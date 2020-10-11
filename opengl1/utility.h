#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>
#include <random>

#include "VertexBuffer.h"
#include "VertexArray.h"



/************************************************************************************************************************************/
/* Constant Values                                                                                                                  */
/************************************************************************************************************************************/

const unsigned int VERTICES_SIZE = 12;                          /*Size of vertices array, contains the number of points to displayed*/


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";



/************************************************************************************************************************************/
/* Global variables                                                                                                                 */
/************************************************************************************************************************************/
int success;
char infoLog[512];
std::random_device rd;
std::mt19937 gen(rd());                                         // Mersenne twister PRNG, initialized with seed from previous random device instance
std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);
unsigned int VBO, VAO, EBO;

std::array<float, VERTICES_SIZE> vertices {
          0.5f,  0.5f, 0.0f,  // top right
          0.5f, -0.5f, 0.0f,  // bottom right
         -0.5f, -0.5f, 0.0f,  // bottom left
         -0.5f,  0.5f, 0.0f   // top left 
     };

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};

/************************************************************************************************************************************/
/* Local function definitions                                                                                                       */
/************************************************************************************************************************************/
void Normal_Distribution(float*);
void Update_Vertices(void);
void Draw(int, VertexArray&, VertexBuffer&);

void Update_Vertices(void) {

    double current_time = glfwGetTime();
    static double old_time = current_time;
  
    if (current_time != 0.0 && (current_time - old_time) > 5.0) {
        for (int i = 0; i < VERTICES_SIZE; i++) {
            float sample;
            Normal_Distribution(&sample);
            vertices.at(i) = sample;
        }
        old_time = current_time;
    }
}

void buildShader(int vertexShader, int fragmentShader) {
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
   
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void linkShader(int vertexShader, int fragmentShader, int shaderProgram) {
    // link shaders

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Draw(int shaderProgram, VertexArray& va, VertexBuffer& vb) {
    // render
    // ------
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    glUseProgram(shaderProgram);
    va.Bind();
    //glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //glBindVertexArray(0); // no need to unbind it every time 
    
    Update_Vertices();
    vb.setData(&vertices, sizeof(vertices));
}



void Normal_Distribution(float * sample) {

    static const float mean = distribution(generator);
    static const float variance = distribution(generator);

    // instance of class std::normal_distribution with specific mean and stddev
    std::normal_distribution<float> d(mean, variance);

    float x = d(gen);
    *sample = x / (1 + std::abs(x)); // *sample in range [-1, 1] using sigmoid function
}

void deAllocateResources() {

}