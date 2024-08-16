﻿#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VAO.h"
#include "shaderClass.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include <vector>

std::vector<float> vertices =
{ //     COORDINATES         /        COLORS      
    -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,
    -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
     0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
     0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,
     0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f
};

// Indices for vertices order
std::vector<unsigned int> indices =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1600;

GLFWwindow* GLInit() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGL();
    return window;
}

Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0, 0, 2));



int main()
{
    auto window = GLInit();
    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window))
    {
        auto shader = Shader("shader/shader.vert","shader/shader.frag");
        auto vao = VAO(vertices,indices);
        
        processInput(window);
        glClearColor(0.5,0.5,0.8,1);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        shader.use();
        
        vao.draw();
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}