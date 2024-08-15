#pragma once

#include <glad/glad.h>

class VBO
{
public:
	GLuint ID;

	VBO(float* vertices, size_t size);

	void Bind();

	void Unbind();

	void Delete();

};

