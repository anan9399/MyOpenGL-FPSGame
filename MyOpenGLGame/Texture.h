#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<vector>

class Texture
{
public:

	static Texture& GetInstance()
	{
		static Texture instance;
		return instance;
	}

	unsigned int loadTexture(char const* path);
	//static bool LoadT8(GLuint& texture, LPCWSTR filename);
	unsigned int loadTextureBySlot(const char* filename, GLint internalFormat, GLint Format, int textureSlot);
	unsigned int loadSkyboxRes(std::vector<std::string> faces);
};

