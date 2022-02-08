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
#include "Terrain.h"
#include "Model.h"
#include "WaterFrameBuffer.h"
#include "Enermy.h"
#include "Player.h"
#include "Raytest.h"
#include "ParticleSystem.h"
#include"Weapon.h"

class Game
{

public:
	const int Screen_Width = 1600;
	const int Screen_Height = 1200;
	int time = glfwGetTime();
	void run();
	static float GetTerrainHeight(float x, float z);
	void SetExePath(std::string path) {
		this->exePath = path;
	}

private:
	void processInput(GLFWwindow* window, float dt);
	//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void Init();
	void Gameloop();
	void InitLight();
	void EnemyBorn(int n);
	void DrawEnermy(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn, std::vector<Enermy*>enermys);
	void AttackUpdate(Player *player);
	void DrawGun(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn);
	unsigned int quadVAO, quadVBO;
	unsigned int framebuffer, textureColorbuffer, rbo;
	int TotalEnermyNum, CurrentEnermyNum;
	bool WeaponSwitch = false,move=false;
	int WeaponMod=1;

	std::string exePath;
	GLFWwindow* window;
	Skybox* skybox;
	Object* object;
	LightDirectional* lightD;
	LightSpot* lightS;
	Model* treeModel,*enermyModel,*stoneModel,*GunModel;
	Shader* terrainShader,*screenShader,*gunShader;
	Shader *enermyShader;
	WaterFrameBuffer* fbos;
	Weapon* weapon;
	Player* player;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	std::vector<Enermy*>enermies;
	std::vector<Enermy*>DeadEnermies;
	
};

