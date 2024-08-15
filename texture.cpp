#include "texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, STBI_rgb_alpha);
	//glActiveTexture(slot);
	glGenTextures(1, &ID);
	glBindTexture(texType, ID);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// 设置纹理的环绕方式
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);//u
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);//TemV
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType , bytes);
	glGenerateMipmap(texType);
	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLenum unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
