#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"
#include "VAO.h"
#include "shaderClass.h"
#include <glm/glm.hpp>
/*#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>*/
#include "camera.h"
#include <vector>
#include "load.h"
//#include "structs.h"
#include "loadin.hpp"

#define camera_shaders "shader/camera.vert","shader/camera.frag"
#define texture_shaders "shader/texture.vert","shader/texture.frag"
#define light_shaders "shader/light.vert","shader/light.frag"

std::vector<float> vertices =
{
    //     COORDINATES         /        COLORS         // UV
    -0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
    0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
    0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f
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

std::vector<float> lightVertices =
{ //     COORDINATES     //
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};

std::vector<unsigned int> lightIndices =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};


std::vector<unsigned int> attribs = {3, 3, 2};
std::vector<unsigned int> attribs2 = {3,3,2};


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1600;

GLFWwindow* GLInit()
{
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

Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0, 0, 2),45,0.1,100);

int main()
{
    camera.setCameraSpeed(0.01f);
    auto window = GLInit();
    glEnable(GL_DEPTH_TEST);

    auto model = md::Model();
    model.loadin("objects/nanosuit.obj");

    auto shader = Shader(texture_shaders);

    //auto texture = Texture("box.png");
    /*auto texture1 = model.meshes[0].mat.diffuse_texture;
    texture1.Bind(1);*/
    shader.setInt("t", 1);
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(window);
        camera.Inputs(window);
        shader.use();
        shader.setMat4("camera_info", camera.Matrix());
        
        
        model.draw(shader);
        
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
