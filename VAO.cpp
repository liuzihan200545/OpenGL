#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint nComponent, GLenum type, size_t stride, void* offsite)
{
	VBO.Bind();
	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, nComponent, type, GL_FALSE, stride, offsite);
	VBO.Unbind();
}


void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);

}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
