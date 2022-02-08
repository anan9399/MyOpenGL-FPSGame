#include "Light.h"





LightDirectional::LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	Position(_position),
	Angles(_angles),
	Color(_color)
{
	UpdateDirection();
	
}

void LightDirectional::UpdateDirection()
{
	Direction = glm::vec3(0, 0, 1.0f);
	Direction = glm::rotateZ(Direction, Angles.z);
	Direction = glm::rotateX(Direction, Angles.x);
	Direction = glm::rotateY(Direction, Angles.y);
	Direction = -1.0f * Direction;
}


LightPoint::LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	Position(_position),
	Angles(_angles),
	Color(_color)
{
	constant = 1.0f;
	linear = 0.9f;
	quadratic = 0.032f;
}

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	Position(_position),
	Angles(_angles),
	Color(_color)
{
	UpdateDirection();
}

void LightSpot::UpdateDirection()
{
	Direction = glm::vec3(0, 0, 1.0f);
	Direction = glm::rotateZ(Direction, Angles.z);
	Direction = glm::rotateX(Direction, Angles.x);
	Direction = glm::rotateY(Direction, Angles.y);
	Direction = -1.0f * Direction;
}

