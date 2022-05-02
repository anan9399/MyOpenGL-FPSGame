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

//void Enermy::DrawEnermy(Camera camera,LightDirectional *lightD,LightSpot *lightS,int FlashOn)
//{
//
//	model = glm::mat4(1.0f);
//	enermyShader->use();
//	view = camera.GetViewMatrix();
//	projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 300.0f);
//	model = glm::translate(model, this->Position);
//	glm::vec3 desiredVelocity = camera.Position - Position;
//	//model = glm::rotate(model, (float)10.0f, glm::vec3(0, 1.0f, 0));
//	enermyShader->setUniform4m("modelMat", model);
//	enermyShader->setUniform4m("viewMat", view);
//	enermyShader->setUniform4m("projectMat", projection);
//
//	enermyShader->setUniform3f("lightD.pos", lightD->Position);
//	enermyShader->setUniform3f("lightD.color", lightD->Color);
//	enermyShader->setUniform3f("lightD.dirToLight", lightD->Direction);
//
//	enermyShader->setUniform3f("lightS.pos", camera.Position);
//	enermyShader->setUniform3f("lightS.color", lightS->Color);
//	enermyShader->setUniform3f("lightS.dirToLight", lightS->Direction);
//	enermyShader->setUniform1f("lightS.cosPhyInner", lightS->cosPhyInner);
//	enermyShader->setUniform1f("lightS.cosPhyOutter", lightS->cosPhyOutter);
//
//
//	enermyShader->setUniform3f("cameraPos", camera.Position);
//
//	//Set Meterial -> Testure
//	enermyShader->setUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
//	enermyShader->setUniform1i("material.diffuse", 0);
//	enermyShader->setUniform1i("material.specular", 1);
//	//myMaterial->shader->setUniform1i("material.emission", Shader::EMISSION);
//	enermyShader->setUniform1f("material.shininess", 64.0f);
//	enermyShader->setUniform1i("FlashOn", FlashOn);
//	if (beAttack) {
//		enermyShader->setUniform1i("Hurt", 1);
//	}
//
//
//	enermyModel->Draw(enermyShader);
//}

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
		fire(dt,player);
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

//elite enemy have particle system
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

