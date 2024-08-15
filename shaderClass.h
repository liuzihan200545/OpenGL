#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<cerrno>

std::string get_file_content(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexfile, const char* fragfile);
	
	void Activate();
	void Delete();

private:

	void checkCompileErrors(unsigned int shader, std::string type);
};

