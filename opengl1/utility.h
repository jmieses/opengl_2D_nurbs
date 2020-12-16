#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>
#include <random>
#include <vector>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


/************************************************************************************************************************************/
/* Constant Values                                                                                                                  */
/************************************************************************************************************************************/

const unsigned int VERTICES_SIZE = 12;                          /*Size of vertices array, contains the number of points to displayed*/




/************************************************************************************************************************************/
/* Global variables                                                                                                                 */
/************************************************************************************************************************************/
// static int success;
// static char infoLog[512];

unsigned int VBO, VAO, EBO;

std::vector<float> vertices {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
         0.45f, 0.5f, 0.0f
    };

std::vector<float> vertices_2 { // place holder vector to initialize OpenGL pipeline
        0.0f, 0.0f, 0.0f,  
        0.0f, 0.0f, 0.0f,  
        0.0f, 0.0f, 0.0f   
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
    static constexpr float TIME_LAPSE = 5.0;
  
    if (current_time != 0.0 && (current_time - old_time) > TIME_LAPSE) {

        for (int i = 0; i < vertices.size(); i++) {
            float sample;
            Normal_Distribution(&sample);
            vertices.at(i) = sample;
        }
        old_time = current_time;
    }
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
    glPointSize(10);
    glDrawArrays(GL_POINTS, 0, 6);

    /*No use of glDrawElements here since we're only drawing points and do not care about order of point drawing. Not use of index buffer. */
    //glDrawElements(GL_POINTS, 6, GL_UNSIGNED_INT, 0);
    
    Update_Vertices();
    vb.setData(&vertices.front(), vertices.size() * sizeof(float));
}

void Dynamic_Draw(std::vector<float>& points, VertexArray& va, VertexBuffer& vb, Shader& shader){

    // glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);

    shader.Use();
    vb.BindDynamic(points);

    va.Bind();

    glDrawArrays(GL_POINTS, 0, points.size() / 3);

    Update_Vertices();
}

void Normal_Distribution(float * sample) {

    static std::random_device rd;
    static std::mt19937 gen(rd());  // Mersenne twister PRNG, initialized with seed from previous random device instance
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);

    static const float mean = distribution(generator);
    static const float std_dev = distribution(generator);
                                            
    static std::normal_distribution<float> normal_distribution(mean, std_dev);  // instance of class std::normal_distribution with specific mean and stddev

    float x = normal_distribution(gen);
    *sample = x / (1 + std::abs(x)); // *sample in range [-1, 1] using sigmoid function
}

// void deCasteljau(){
//     std::vector<float> temp_control_points(vertices);

//     for(unsigned int i = 1; i < temp_control_points.size(); i++){
//         for(unsigned int j = 0; j < temp_control_points.size() - i; j++){
//             temp_control_points[j].x = (1.0 - u) * temp_control_points[j].x + u * temp_control_points[j + 1].x;
//             temp_control_points[j].y = (1.0 - u) * temp_control_points[j].y + u * temp_control_points[j + 1].y;
//         }
//     }

//     curve.C[0].x = temp_control_points[0].x;
//     curve.C[0].y = temp_control_points[0].y;
// }

void deAllocateResources() {

}