#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>


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
	float normal_speed;
	float sensitivity = 100.0f;

	float fov;
	float near;
	float far;

	glm::mat4 project_result;

	Camera(int width, int height, glm::vec3 position,float FOVdeg, float nearPlane, float farPlane);

	// Updates and exports the camera matrix to the Vertex Shader
	glm::mat4 Matrix();
	// Handles camera inputs
	void Inputs(GLFWwindow* window);

	void setCameraSpeed(float _speed);
	
	void updataProperties(float FOVdeg, float nearPlane, float farPlane);
};

