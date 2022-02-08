#pragma once
#include"Particle.h"
#include<vector>
#include  "Shader.h"
#include"LightDirectional.h"
#include"LightSpot.h"
#include"Camera.h"
#include"Texture.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class ParticleSystem
{
public:
	ParticleSystem();
	void init(int numOfParticles);
	void update(float dt);
	void aging(float dt);
	void kinematics(float dt);
	void prepare();
	void draw(Camera& camera, float dt, glm::vec3 startPos);

	std::vector<Particle> particles;
	std::vector<glm::vec3> positions;
private:
	Shader* PaticleShader;
	unsigned int P_VAO, P_VBO,P_EBO;
	unsigned int P_texture;
};

