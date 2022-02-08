#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include"RandomNum.h"

class Particle
{
public:
	Particle();
	~Particle();
	glm::vec3 Position;
	glm::vec3 Velocity;
	glm::vec3 origin;
	glm::vec3 color;
	float age;
	float life;

	bool Update(float dt);
	void SetOrigin(glm::vec3 originPos);

	
};

