#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	Position(_position),
	Angles(_angles),
	Color(_color)
{
	UpdateDirection();
}

LightSpot::~LightSpot()
{
}

void LightSpot::UpdateDirection()
{
	Direction = glm::vec3(0, 0, 1.0f);
	Direction = glm::rotateZ(Direction, Angles.z);
	Direction = glm::rotateX(Direction, Angles.x);
	Direction = glm::rotateY(Direction, Angles.y);
	Direction = -1.0f * Direction;
}

void LightSpot::UpdateLightSVector(Camera& camera)
{
	Direction = -camera.Forward;
}
