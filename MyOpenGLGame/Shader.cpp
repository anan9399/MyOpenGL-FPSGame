#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath ) {
	ifstream vertexFile;
	ifstream fragmentFile;
	ifstream geometryFile;

	stringstream vertexSString;
	stringstream fragmentSString;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw exception("fail to open file");
		}
		vertexSString << vertexFile.rdbuf();	
		fragmentSString << fragmentFile.rdbuf();

		vertexString = vertexSString.str();
		fragmentString = fragmentSString.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		// if geometry shader path is present, also load a geometry shader
		if (geometryPath != nullptr)
		{
			geometryFile.open(geometryPath);
			std::stringstream geometrySString;
			geometrySString << geometryFile.rdbuf();
			geometryString = geometrySString.str();
			geometryFile.close();
			geometrySource = geometryString.c_str();
		}


	/*	std::cout << vertexSource;
		std::cout << fragmentSource;*/

		unsigned vertex, fragment;
		
		//Compile Shaders
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		// if geometry shader is given, compile geometry shader
		unsigned int geometry;
		if (geometryPath != nullptr)
		{
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &geometrySource, NULL);
			glCompileShader(geometry);
		}

		//Link Shaders
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		if (geometryPath != nullptr)
			glAttachShader(ID, geometry);

		//Delete Shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != nullptr)
			glDeleteShader(geometry);


	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
	}
}
	
void Shader::use() {
	glUseProgram(ID);
}

void Shader::stop()
{
	glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, int slot) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), slot);
}

void Shader::setUniform1f(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}


void  Shader::setUniform3f(const std::string& name, const glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()),value.x,value.y,value.z);
}
void Shader::setUniform4f(const std::string& name, const glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z,value.w);
}
void  Shader::setUniform4m(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}


