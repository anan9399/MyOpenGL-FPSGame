#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"
#include "LightDirectional.h"
#include "LightSpot.h"
#include "Shader.h"
#include "Camera.h"
#include "Terrain.h"
#include "Player.h"
#include "RandomNum.h"
#include "ParticleSystem.h"
#define PI 3.1415926

class Enermy
{
	
public:
	Enermy(bool live=true);
	glm::vec3 Position,currentVelocity;
	glm::vec3 front= glm::vec3(0, 0, 1.0f);
	float MaxSpeed,BackSpeed;
	float ToAngle;
	float Angle;
	double Forward;
	double lastForward=0;
	float AttackDuration,HurtDuration;
	float AttackDistance;
	float size;
	float hp;
	bool active;
	bool alive;
	bool canAttack;
	bool beAttack;
	bool Hurt;
	bool Elite;
	void ActiveEnermy(glm::vec3& Pos);
	void DrawEnermy(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn);
	void DrawDeadEnermy(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn);
	float CalcDistance(glm::vec3& enemyPos, glm::vec3& playerPos);
	float CalcDistanceNoHeight(glm::vec3& enemyPos, glm::vec3& playerPos);
	void Update(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn, Player* player, const float dt);
	void beHit();
	void DrawParticle(Camera& camera, const float dt);
private:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	void fire(const float dt, Player* player);
	void Seek(Camera& target, const float dt);
	void Attack(Player* player, const float dt,float PlayerDistance);
	void BackAway(Camera& target, const float dt, int mod=1);
	
	ParticleSystem* particleSystem;
};

