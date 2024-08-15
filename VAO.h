#pragma once

#include "VBO.h"

class VAO
{
public:
	GLuint ID;
	
	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint nComponent, GLenum type, size_t stride, void* offsite);

	void Bind();

	void UnBind();

	void Delete();
};

