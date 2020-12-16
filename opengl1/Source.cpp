#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utility.h"
#include <iostream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Error_Handling.h"
#include "Shader.h"
#include "Curve.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // During init, enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
    std::cout << glGetString(GL_VERSION) << '\n';

    Shader shader("vertex_shader.vs", "fragment_shader.fs");
    Shader shader_2("vertex_shader_2.vs", "fragment_shader_2.fs");

    VertexArray dynamic_vertex_array;
    VertexBuffer dynamic_vertex_buffer(vertices, false);
    VertexBufferLayout dynamic_layout;
    dynamic_layout.Push<float>(3);
    dynamic_vertex_array.AddBuffer(dynamic_vertex_buffer, dynamic_layout);
    glEnableVertexAttribArray(0);

    VertexArray dynamic_vertex_array_2;
    VertexBuffer dynamic_vertex_buffer_2(vertices_2, false);
    VertexBufferLayout dynamic_layout_2;
    dynamic_layout_2.Push<float>(3);
    dynamic_vertex_array_2.AddBuffer(dynamic_vertex_buffer_2, dynamic_layout_2);
    glEnableVertexAttribArray(0);

    Curve curve;
    // render loop
    // -----------
    glPointSize(10);
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        std::vector<float>tmp(curve.deCasteljau(vertices));
        glPointSize(2);
        Dynamic_Draw(tmp, dynamic_vertex_array_2, dynamic_vertex_buffer_2, shader_2);
        glPointSize(5);
        Dynamic_Draw(vertices, dynamic_vertex_array, dynamic_vertex_buffer, shader);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
} 



/*5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555*/
/*5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555*/
/*5555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555*/
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// #include <iostream>

// #include <vector>
// #include "Shader.h"
// #include "VertexBuffer.h"
// #include "VertexArray.h"
// #include "VertexBufferLayout.h"
// #include "utility.h"

// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void processInput(GLFWwindow *window);

// // settings
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;

// const char *vertexShaderSource = "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "}\0";
// const char *vertexShader2Source = "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "}\0";
// const char *fragmentShader1Source = "#version 330 core\n"
//     "out vec4 FragColor;\n"
//     "void main()\n"
//     "{\n"
//     "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//     "}\n\0";
// const char *fragmentShader2Source = "#version 330 core\n"
//     "out vec4 FragColor;\n"
//     "void main()\n"
//     "{\n"
//     "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
//     "}\n\0";


// int main()
// {
//     // glfw: initialize and configure
//     // ------------------------------
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif

//     // glfw window creation
//     // --------------------
//     GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//     if (window == NULL)
//     {
//         std::cout << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwMakeContextCurrent(window);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     // glad: load all OpenGL function pointers
//     // ---------------------------------------
//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cout << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }


//     // build and compile our shader program

//     Shader shader1("vertex_shader.vs", "fragment_shader.fs");
//     Shader shader2("vertex_shader_2.vs", "fragment_shader_2.fs");
//     // set up vertex data (and buffer(s)) and configure vertex attributes
//     // ------------------------------------------------------------------
//     std::vector<float> firstTriangle{
//         -0.9f, -0.5f, 0.0f,  // left 
//         -0.0f, -0.5f, 0.0f,  // right
//         -0.45f, 0.5f, 0.0f,  // top 
//     };
    
//     std::vector<float> secondTriangle {
//         0.0f, -0.5f, 0.0f,  // left
//         0.9f, -0.5f, 0.0f,  // right
//         0.45f, 0.5f, 0.0f   // top 
//     };
//     //unsigned int VBOs[2], VAOs[2];


//     // first triangle setup
//     // --------------------
//     VertexArray va1;
//     VertexBuffer vb1(firstTriangle, false);
//     VertexBufferLayout layout1;
//     layout1.Push<float>(3);
//     va1.AddBuffer(vb1, layout1);

//     glEnableVertexAttribArray(0);
//     // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
//     // second triangle setup
//     // ---------------------

//     VertexArray va2;
//     VertexBuffer vb2(secondTriangle, false);
//     VertexBufferLayout layout2;
//     layout2.Push<float>(3);
//     va2.AddBuffer(vb2, layout2);
//     glEnableVertexAttribArray(0);
//     // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)


//     // uncomment this call to draw in wireframe polygons.
//     //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//     // render loop
//     // -----------
//     while (!glfwWindowShouldClose(window))
//     {
//         // input
//         // -----
//         processInput(window);

//         // render
//         // ------
//         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         // now when we draw the triangle we first use the vertex and orange fragment shader from the first program
//         //glUseProgram(shaderProgramOrange);
//         //shader1.Use();
//         // draw the first triangle using the data from our first VAO
//         // glBindBuffer(GL_ARRAY_BUFFER,  VBO1);
//         // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(firstTriangle), &firstTriangle.front());
//         // glBindVertexArray(VAO1);
//         // glDrawArrays(GL_TRIANGLES, 0, 3);   // this call should output an orange triangle

//         Dynamic_Draw(firstTriangle, va1, vb1, shader1);

//         // then we draw the second triangle using the data from the second VAO
//         // when we draw the second triangle we want to use a different shader program so we switch to the shader program with our yellow fragment shader.
//         //glUseProgram(shaderProgramYellow);
//         // shader2.Use();
//         // glBindBuffer(GL_ARRAY_BUFFER,  VBO2);
//         // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(firstTriangle), &secondTriangle.front());
//         // glBindVertexArray(VAO2);
//         // glDrawArrays(GL_TRIANGLES, 0, 3);   // this call should output a yellow triangle

//         Dynamic_Draw(secondTriangle, va2, vb2, shader2);

//         // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//         // -------------------------------------------------------------------------------
//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     // optional: de-allocate all resources once they've outlived their purpose:
//     // ------------------------------------------------------------------------
//     //glDeleteVertexArrays(2, VAOs);
//     //glDeleteBuffers(2, VBOs);
//     //glDeleteProgram(shaderProgramOrange);
//     //glDeleteProgram(shaderProgramYellow);

//     // glfw: terminate, clearing all previously allocated GLFW resources.
//     // ------------------------------------------------------------------
//     glfwTerminate();
//     return 0;
// }

// // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// // ---------------------------------------------------------------------------------------------------------
// void processInput(GLFWwindow *window)
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, true);
// }

// // glfw: whenever the window size changed (by OS or user resize) this callback function executes
// // ---------------------------------------------------------------------------------------------
// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     // make sure the viewport matches the new window dimensions; note that width and 
//     // height will be significantly larger than specified on retina displays.
//     glViewport(0, 0, width, height);
// }