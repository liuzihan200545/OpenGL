#pragma once
#include <glad/glad.h>
#include "stb_image.h"
#include "shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLenum unit);
	
	void Bind();
	
	void Unbind();
	
	void Delete();
};

