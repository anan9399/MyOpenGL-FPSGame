#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<vector>

#include "Shader.h"
#include"Texture.h"
#include"Camera.h"

class Skybox
{
public:
	Skybox();
	~Skybox();
	void InitSkybox();
	void draw(Camera camera, int Screen_Width = 1600,int Screen_Height = 1200);

private:
	Shader* m_shader;
	unsigned int VAO, VBO;
	unsigned int m_texture;
};

