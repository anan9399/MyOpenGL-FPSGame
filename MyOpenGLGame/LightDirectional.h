#pragma once
#include <glm/glm.hpp>
#include<glm/gtx/rotate_vector.hpp>
class LightDirectional
{
public:
	LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));

	//~LightDirectional();

	glm::vec3 Position;
	glm::vec3 Angles;
	glm::vec3 Color;
	glm::vec3 Direction = glm::vec3(0, 0, 1.0f);

	void UpdateDirection();
};

