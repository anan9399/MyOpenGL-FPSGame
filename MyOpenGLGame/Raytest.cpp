#include "Raytest.h"

Raytest::Raytest()
{
	castRay = false;
	RayHit = false;
}

void Raytest::Update(Camera& camera, float dt, std::vector<Enermy*> enermies,int mod, irrklang::ISoundEngine* SoundEngine)
{
	if (castRay) {
		if (mod != 0) {
			castRay = false;
			PlayerRay = CastRayFromCamera(camera);
			CheckRaySphereCollision(camera, enermies);
			SoundEngine->setSoundVolume(1.5f);
			SoundEngine->play2D("audio/solid.wav");
			SoundEngine->setSoundVolume(0.5f);
		}
		else if (mod == 0) {
			castRay = false;
			PlayerCloseFight(camera, enermies);
		}
	}
}

//Enemy take damage
void Raytest::HitEnermy(Enermy* enermy)
{
	enermy->beHit();
}

//make a ray from camera
Ray Raytest::CastRayFromCamera(Camera& camera)
{
	Ray ray;
	ray.Dir = camera.Forward;
	ray.Pos = camera.Position;
	return ray;
}

//Enable Ray
void Raytest::CastRay()
{
	castRay = true;
}

//Player Close Fight
void Raytest::PlayerCloseFight(Camera& camera, std::vector<Enermy*> enermies)
{
	//check all alive enemies 
	for (auto i = enermies.begin(); i != enermies.end(); ++i) {
		//If they are close enough to the player, be hit
		if ((*i)->alive && (*i)->CalcDistance((*i)->Position,camera.Position) <= 10.0f) {
			HitEnermy((*i));
		}
	}
}

//check whether the ray hit the enemies
void Raytest::CheckRaySphereCollision(Camera& camera, std::vector<Enermy*> enermies)
{
	//check all alive enemies 
	for (auto i = enermies.begin(); i != enermies.end(); i++) {
		if ((*i)->alive) {
			
			RayHit = RaySphere(camera, PlayerRay.Dir, 1.5f, (*i)->Position);
			if (RayHit) {
				HitEnermy((*i));
				//break;
			}
		}
	}
}

//make a Sphere form the position and check whether the ray hit the Sphere
bool Raytest::RaySphere(Camera& camera, glm::vec3 RayDirWorld, double SphereRadius, glm::vec3 pos)
{
	// work out components of quadratic
	glm::vec3 v = pos - camera.Position;
	long double a = glm::dot(RayDirWorld, RayDirWorld);
	long double b = 2.0 * glm::dot(v, RayDirWorld);
	long double c = glm::dot(v, v) - SphereRadius * SphereRadius;
	long double b_squared_minus_4ac = b * b + (-4.0) * a * c;

	if (b_squared_minus_4ac == 0)
	{
		// One real root 
		return true;
	}
	else if (b_squared_minus_4ac > 0)
	{
		// Two real roots 
		long double x1 = (-b - sqrt(b_squared_minus_4ac)) / (2.0 * a);
		long double x2 = (-b + sqrt(b_squared_minus_4ac)) / (2.0 * a);

		if (x1 >= 0.0 || x2 >= 0.0)
			return true;
		if (x1 < 0.0 || x2 >= 0.0)
			return true;
	}

	// No real roots
	return false;
}
