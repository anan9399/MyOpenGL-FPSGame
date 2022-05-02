#pragma once
#include"Shader.h"
#include"LightDirectional.h"
#include"LightSpot.h"
#include"Camera.h"
#include"Texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>



class Object
{
public:
	void InitObject();
	
	void InitGrass(std::vector<glm::vec3>GrassPos);
	void Drawcube(Camera &camera, const LightDirectional *lightD, const LightSpot *lightS,int FlashOn);
	void DrawPlant( Camera& camera, const LightDirectional* lightD, const LightSpot* lightS, int FlashOn, std::vector<glm::vec3>plantPos);
	void DrawWater(Camera& camera, const LightDirectional* lightD, const LightSpot* lightS, int FlashOn,int reflect);
	void DrawCrosshair();
	void DrawEnd(int end = 0);

private:
	unsigned int VAO, VBO;
	unsigned int PlantVAO, PlantVBO, PlantInsVBO;
	unsigned int WaterVAO, WaterVBO;
	unsigned int ScreenVAO, ScreenVBO;
	unsigned int FullScreenVAO, FullScreenVBO;


	Shader* m_shader;
	Shader* plant_shader;
	Shader* water_shader;
	Shader* ScreenShader;
	Shader* FullScreenShader;

	LightDirectional *m_lightD;
	//Terrain* terrain;
	//LightPoint* m_lightP;
	//LightSpot* m_lightS;
	glm::vec3 ambient = glm::vec3(1.0f);
	int diffuse, specular;
	int plantTex;
	int waterTex;
	int AimTex;
	int winTex, loseTex;

	//std::vector<Tree> trees;

	std::vector<glm::mat4> GrassModel;
};


