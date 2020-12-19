#include <windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


/************************************************************************************************************************************/
/* Local Includes                                                                                                                   */
/************************************************************************************************************************************/
#include "utility.h"
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
        glPointSize(2);
        Dynamic_Draw(curve.Bspline(vertices), dynamic_vertex_array_2, dynamic_vertex_buffer_2, shader_2);
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