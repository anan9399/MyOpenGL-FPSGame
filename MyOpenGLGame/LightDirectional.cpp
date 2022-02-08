#include "LightDirectional.h"

LightDirectional::LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color):
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
