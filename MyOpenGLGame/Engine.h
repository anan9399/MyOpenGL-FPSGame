#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>

#include "LightDirectional.h"
#include "LightSpot.h"
#include "Shader.h"
#include "Camera.h"
#include "Skybox.h"
#include "Object.h"
#include"Terrain.h"
#include"Model.h"
#include"WaterFrameBuffer.h"
#include"Enermy.h"
#include<vector>

class Engine
{
public:
	const int Screen_Width = 1600;
	const int Screen_Height = 1200;
	int time = glfwGetTime();
	void run();

	void SetExePath(std::string path) {
		this->exePath = path;
	}

private:
	void Init();
	void Gameloop();
	void processInput(GLFWwindow* window, float dt);
	unsigned int quadVAO, quadVBO;
	unsigned int VBO, VAO, EBO, TVBO, NVBO;
	unsigned int framebuffer, textureColorbuffer, rbo;
	int texture_1, texture_2, texture_3, blendmap;
	unsigned int waterTex;
	std::string exePath;
	GLFWwindow* window;
	Skybox* skybox;
	Object* object;
	//Terrain* terrain;
	LightDirectional* lightD;
	LightSpot* lightS;
	Model* treeModel;
	Shader* terrainShader, * treeShader, * screenShader;
	Shader* WaterShader;
	WaterFrameBuffer* fbos;
	Enermy* enermy;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
};

