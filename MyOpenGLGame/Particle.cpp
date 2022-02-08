#include "Particle.h"

Particle::Particle() :
	Position(glm::vec3(350,10,350)),
	Velocity(glm::vec3(RandomNum::GetInstance().GetRandomNumber1f(-1.0, 1.0), RandomNum::GetInstance().GetRandomNumber1f(0.5f, 2.0f), RandomNum::GetInstance().GetRandomNumber1f(-1.0, 1.0))),
	origin(glm::vec3(350, 10, 350)),
	color(glm::vec3(1.0f)),
	age(0),
	life(RandomNum::GetInstance().GetRandomNumber1f(0, 1.5f))
{
	
}

Particle::~Particle()
{
}

bool Particle::Update(float dt)
{
	age += dt;
	if (age > life) {
		Position = origin;
		Velocity = glm::vec3(RandomNum::GetInstance().GetRandomNumber1f(-1.0, 1.0), RandomNum::GetInstance().GetRandomNumber1f(0.0, 5.0), RandomNum::GetInstance().GetRandomNumber1f(-1.0, 1.0));
		age = 0.0f;
	}
	else {
		 Position += Velocity * dt;
	}

	return true;
}

void Particle::SetOrigin(glm::vec3 originPos)
{
	origin = originPos;
}





