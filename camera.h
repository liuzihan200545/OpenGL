#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include "shaderClass.h"
#include "shaderClass.h"


class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = { 0,0,-1 };
	glm::vec3 Up = { 0,1,0 };

	bool firstClick = true;

	int width;
	int height;

	float speed = 0.1f;
	float sensitivity = 100.0f;

	Camera(int width, int height, glm::vec3 position);

	// Updates and exports the camera matrix to the Vertex Shader
	void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window);

};

