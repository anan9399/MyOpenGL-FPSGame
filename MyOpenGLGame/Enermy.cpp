#include "Enermy.h"


Enermy::Enermy( bool live)
{
	this->Position = glm::vec3(350.0f, -999.0f, 350.0);
		//glm::vec3(350.0f, 13.0f, 350.0);
	MaxSpeed = RandomNum::GetInstance().GetRandomNumber1f(3.5f,5.5f);
	BackSpeed = 20 * MaxSpeed;
	hp = 100;
	currentVelocity = glm::vec3(1.0f, 1.0f, 1.0f);
	canAttack = false;
	AttackDuration = 0.0f;
	HurtDuration = 0.0f;
	beAttack = false;
	active = false;
	alive = live;
	Hurt = false;
	Elite = false;
	float eliteCheck = live? RandomNum::GetInstance().GetRandomNumber1f(0.0, 1.0): 1.0f;
	Elite = (eliteCheck < 0.2f) ? true : false;
	AttackDistance = Elite ?  20.0f : 3.0f;
	if (Elite) {
		std::cout << "elite born" << std::endl;
		particleSystem = new ParticleSystem();
		particleSystem->init(8);
	}

}

void Enermy::ActiveEnermy(glm::vec3& Pos)
{
	Position = Pos;
	active = true;
}

void Enermy::DrawDeadEnermy(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn)
{
}

float Enermy::CalcDistance(glm::vec3& enemyPos, glm::vec3& playerPos)
{
	return sqrt(powf(enemyPos.x - playerPos.x, 2.0f) + powf(enemyPos.y - playerPos.y, 2.0f) + powf(enemyPos.z - playerPos.z, 2.0f));
}

float Enermy::CalcDistanceNoHeight(glm::vec3& enemyPos, glm::vec3& playerPos)
{
	return sqrt(powf(enemyPos.x - playerPos.x, 2.0f) + powf(enemyPos.z - playerPos.z, 2.0f));
}


//Enemy status update
void Enermy::Update(Camera camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn,Player *player, const float dt)
{
	float distance = CalcDistance(this->Position, camera.Position);
	Hurt = false;
	//std::cout << distance << std::endl;
	if (alive) {
		//if enemy is close enough to the player, begin to attack player
		if (distance < AttackDistance && canAttack) {
			Attack(player, dt, distance);
		}
		//if player is far enough to the enemy, begin to move
		//if player is too far to the enemy, enemy sleep
		else if (distance > AttackDistance && distance < 200) {
			Seek(camera, dt);
		}
		//enemy hurt
		if (beAttack) {
			if (HurtDuration >= 1.0f) {
				hp -= player->atk;
				BackAway(camera, dt,player->GetWeapon());
				HurtDuration = 0;
				Hurt = true;
				beAttack = false;	
			}
			else
			{
				beAttack = false;
			}
		}
		if (HurtDuration <= 1.0f) {
			HurtDuration += 2 * dt;
		}

		//enemy attack 
		if (AttackDuration >= 1.0f) {
			AttackDuration = 0.0f;
			if (!canAttack)
				canAttack = true;
		}
		else {
			AttackDuration += 0.8 * dt;
		}
		//get the y-coordinate form terrain
		if (active) {
			this->Position.y = Terrain::GetInstance().GetTerrainHeight(this->Position.x, this->Position.z) + 5.0f;
		}
		//enemy dead check
		if (hp <= 0)
		{
			alive = false;
		}
	}
		
}


void Enermy::fire(const float dt,Player *player)
{
	std::cout << "enermy fire!" << std::endl;
	std::cout << "hp: " << player->hp << std::endl;
	player->beAttack(5);
	canAttack = false;
}

void Enermy::Seek(Camera& target, const float dt)
{
	//Steps 1-3: Calculating the desired velocity
	glm::vec3 desiredVelocity = target.Position - Position;
	desiredVelocity = glm::normalize(desiredVelocity);
	desiredVelocity *= MaxSpeed;


	//Steps 4-5: Calculating the steering force
	glm::vec3 steeringForce = desiredVelocity - currentVelocity;
	//Limit the magnitude of Vector (steering force) to the maximum force
	steeringForce = glm::clamp(steeringForce, -MaxSpeed, MaxSpeed);

	glm::vec3 newVelocity = currentVelocity + steeringForce;
	newVelocity = glm::clamp(newVelocity, -MaxSpeed, MaxSpeed);
	//Angle = glm::acos(glm::dot(glm::normalize(currentVelocity), glm::normalize(newVelocity)));
	//std::cout << Angle * 180 /3.14 << std::endl;
	//currentVelocity = glm::normalize(newVelocity);

	Position += newVelocity * dt;
}

void Enermy::Attack(Player* player, const float dt, float PlayerDistance)
{
	if (PlayerDistance <= 3) {
		std::cout <<"hp: " <<player->hp << std::endl;
		player->beAttack(5);
		canAttack = false;
	}
	if (Elite) {
		fire(dt);
	}
	
	//std::cout << player->hp << std::endl;
}

//if enemy get hit ,go back away
// accroding to player's weapon , close fight make the enemy go more back away 
void Enermy::BackAway(Camera& target, const float dt,int mod)
{
	//std::cout << mod;
	glm::vec3 desiredVelocity = target.Position - Position;
	desiredVelocity = glm::normalize(desiredVelocity);
	desiredVelocity *= BackSpeed;
	if (mod == 0) {
		desiredVelocity *= 5;
	}
	glm::vec3 steering = desiredVelocity - currentVelocity;
	steering = glm::clamp(steering, -BackSpeed, BackSpeed);
	
	Position -= steering * dt;
}

void Enermy::DrawParticle(Camera& camera, const float dt)
{
	if (Elite) {
		particleSystem->draw(camera, dt, Position);
	}
}

//Enable the hurt status
void Enermy::beHit()
{
	beAttack = true;
}

