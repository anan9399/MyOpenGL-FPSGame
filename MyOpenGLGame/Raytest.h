#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Enermy.h"

class Ray {
public:
	glm::vec3 Dir;
	glm::vec3 Pos;
};
class Raytest
{
public:
	Raytest();
	bool castRay;
	void Update(Camera& camera, float dt, std::vector<Enermy*> enermies, int mod);
	void HitEnermy(Enermy* enermy);
	Ray CastRayFromCamera(Camera& camera);
	void CastRay();
	void PlayerCloseFight(Camera& camera, std::vector<Enermy*> enermies);
private:
	bool RayHit;
	Ray PlayerRay; 
	void CheckRaySphereCollision(Camera& camera, std::vector<Enermy*> enermies);
	bool RaySphere(Camera& camera, glm::vec3 RayDirWorld, double SphereRadius,glm::vec3 pos);
};

