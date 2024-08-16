#pragma once
#include <glad/glad.h>

#include "stb_image.h"
#include "shaderClass.h"
#include <string>
#include <iostream>

class Texture {
public:
	Texture() : m_RendererID(0), m_FilePath(""), m_LocalBuffer(nullptr),
		m_Width(0), m_Height(0), m_BPP(0) {}

	Texture(const std::string& path)
		: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr),
		m_Width(0), m_Height(0), m_BPP(0)
	{
		LoadTexture();
	}

	~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Bind(unsigned int slot = 0) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	void LoadTexture()
	{
		stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		if (m_LocalBuffer)
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
            
			glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);
            
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//u
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//TemV

			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

			stbi_image_free(m_LocalBuffer);
		}
		else
		{
			std::cout << "Failed to load texture" << '\n';
		}
	}

private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};

