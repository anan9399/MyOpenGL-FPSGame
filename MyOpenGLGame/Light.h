#pragma once
#include <glm/glm.hpp>
#include<glm/gtx/rotate_vector.hpp>


//class Light
//{
//public:
//
//	Light(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
//	~Light();
//
//	glm::vec3 Position;
//	glm::vec3 Angles;
//	glm::vec3 Color;
//	glm::vec3 Direction = glm::vec3(0, 0, 1.0f);
//
//
//};

class LightDirectional 
{
public:
	LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightDirectional();

	glm::vec3 Position;
	glm::vec3 Angles;
	glm::vec3 Color;
	glm::vec3 Direction = glm::vec3(0, 0, 1.0f);

	void UpdateDirection();
};


class LightPoint
{
public:
	LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint();

	glm::vec3 Position;
	glm::vec3 Angles;
	glm::vec3 Color;
	glm::vec3 Direction = glm::vec3(0, 0, 1.0f);

	float constant;
	float linear;
	float quadratic;
	
};

class LightSpot 
{
public:
	LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightSpot();

	glm::vec3 Position;
	glm::vec3 Angles;
	glm::vec3 Color;
	glm::vec3 Direction = glm::vec3(0, 0, 1.0f);

	//角度越大 cos越接近1
	float cosPhyInner = 0.9f;
	float cosPhyOutter = cosPhyInner - 0.05f;

	void UpdateDirection();
};