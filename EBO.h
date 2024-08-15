#pragma once

#include <glad/glad.h>

class EBO
{
public:
	GLuint ID;

	EBO(unsigned int* indices, size_t size);

	void Bind();

	void Unbind();

	void Delete();

};