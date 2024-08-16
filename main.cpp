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
    loadMesh("objects/cylinder.obj");

    print(vertices_load.size());
    print(indices_load.size());
    
    auto window = GLInit();
    glEnable(GL_DEPTH_TEST);

    auto shader = Shader(texture_shaders);
    auto vao = VAO(vertices, indices, attribs);
    auto texture = Texture("textures/squere.png");

    auto vao_light = VAO(vertices_load,indices_load,attribs2);
    auto shader_light = Shader(light_shaders);
    
    texture.Bind(0);
    shader.setInt("t", 0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        camera.Inputs(window);
        shader.use();
        shader.setMat4("camera_info", camera.Matrix());

        
        vao.draw();

        shader_light.use();
        shader_light.setMat4("camera_info", camera.Matrix());
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,glm::vec3(0,5,0));
        shader_light.setMat4("model",model);
        vao_light.draw();

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
