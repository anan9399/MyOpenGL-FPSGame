#pragma once
#include <fstream>
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
#include "Object.h"
#include"Model.h"
#include"RandomNum.h"

class Terrain
{
public:
#define VERTEX_COUNT 101
#define SIZE 7


	static Terrain& GetInstance()
	{
		static Terrain instance;
		return instance;
	}

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	
	void Init();
	void draw(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn);
	void DrawTree(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn, Model* treeModel, std::vector<glm::vec3>treePosition, glm::vec3 scaleSize);
	int readNum(int* cursor, char str[VERTEX_COUNT * 3 + 10]);
	float GetTerrainHeight(float x, float z);
	void InitStone(Model* stoneModel);

private:
	Terrain();
	void InitWater();
	void DrawWater(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn);
	void DrawStone(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn);

	unsigned int VAO, VBO, EBO, TVBO, NVBO;
	int texture_1, texture_2, texture_3, blendmap;
	unsigned int W_VAO, W_VBO, W_EBO, W_TVBO, W_NVBO;
	int stoneAmount=100;
	int waterTex;
	Shader* terrainShader, * treeShader, *WaterShader,*stoneShader;
	Object* object = new Object();
	Model* stone;

	std::vector<glm::vec3>plantPos;

	std::vector<glm::vec3>  stonesPos, stoneScale;
	std::vector<glm::mat4>  stoneModelMat;

	std::vector<glm::vec3>WaterVertex;
	std::vector<glm::vec3>WaterNormal;
	std::vector<glm::vec2>WaterTexture;
	std::vector<int>WaterIndex;
	
};

