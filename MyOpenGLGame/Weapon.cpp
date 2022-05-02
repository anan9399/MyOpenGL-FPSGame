#include "Weapon.h"

Weapon::Weapon(Player *player)
{
	WeaponMod = 1;
	atkDuration = 1.0f;
	atkDurationMax = 1.0f;
	MaxAmo = 10;
	amo = MaxAmo;
	AnotherAmo = 3;
	reloading = false;
	switching = false;
	runing = false;
	currentReloadTime = 0.0f;
	totalReloadTime = 1.0f;
	QuickReloadMod = false;
	SwitchDuration = 0.0f;
	player->SetAtk(20.0f);
	offset = 0.0;
	offsetRange = 0.001;
	offsetValue = 0.002f;

	Zoffset = 0.0;
	ZoffsetRange = 0.03;
	ZoffsetValue = 0.08f;
}

void Weapon::Upload(Camera camera, std::vector<Enermy*>enermies, irrklang::ISoundEngine* SoundEngine,Raytest * raytest,bool mouse_button,float dt)
{
	if (WeaponMod!= 0) {
		//check whether player is reloading or switching
		if (!reloading && !switching) {
			if (atkDuration >= atkDurationMax && mouse_button) {
				raytest->CastRay();
				std::cout << "WeaponMod: " << WeaponMod << "  Remaining bullets " << amo << std::endl;
				//check the amo
				AmoCheck();
			}
			else if (atkDuration < atkDurationMax) {
				atkDuration += 2 * dt;
			}
		}

		if(reloading)
		{
			Reload(dt);
		}
	}

	else if (atkDuration >= atkDurationMax && mouse_button) {
		raytest->CastRay();
	}
	raytest->Update(camera, dt, enermies, WeaponMod,SoundEngine);


}

void Weapon::AmoCheck()
{
	atkDuration = 0.0f;
	amo--;
	if (amo == 0) {
		reloading = true;
	}
}

bool Weapon::SwitchWeapon(Player *player,int mod,bool WeaponSwitching, float dt)
{
	if (!WeaponSwitching) {
		return false;
	}

	switching = true;
	//std::cout << "switching weapon" << std::endl;
	if (reloading == false && SwitchDuration >= 1.0f ) {
		switching = false;
		SwitchDuration = 0.0f;
		if (mod == 1) {

			//different gun have its own amo data
			//load the parent gun's amo data to anotherAmo
			float maxA=10;
			if (WeaponMod == 2) {
				maxA = amo;
			}
			amo = AnotherAmo;
			AnotherAmo = maxA;
			MaxAmo = 10;
			atkDurationMax = 1.0f;
			atkDuration = atkDurationMax;
			totalReloadTime = 1.0f;
			player->SetAtk(20.0f);
			WeaponMod = mod;
			std::cout << "success switching weapon" << WeaponMod << std::endl;
			return false;
		}
		else if (mod == 2) {

			float maxA =3;
			if (WeaponMod == 1) {
				maxA = amo;
			}
			amo = AnotherAmo;
			AnotherAmo = maxA;
			MaxAmo = 3;
			atkDurationMax = 2.0f;
			atkDuration = atkDurationMax;
			totalReloadTime = 1.3f;
			player->SetAtk(100.0f);
			WeaponMod = mod;
			std::cout << "success switching weapon" << WeaponMod << std::endl;
			return false;
		}
		else {
			

			//AnotherAmo = amo;
			MaxAmo = 999;
			atkDurationMax = 1.2f;
			atkDuration = atkDurationMax;
			totalReloadTime = 0;
			player->SetAtk(1.0f);
			WeaponMod = mod;
			std::cout << "success switching weapon" << WeaponMod << std::endl;
			return false;
		}
		
	}
	else {
		SwitchDuration += 2 * dt;
		return true;
	}


}

void Weapon::Draw(Camera& camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn,bool mod,float dt)
{
	//std::cout << offset << std::endl;
	if (mod == true) {
		Zoffset += ZoffsetValue * dt;
	}
	else {
		Zoffset = 0;
	}

	if (offset > offsetRange) {
		offset = offsetRange;
		offsetValue = -offsetValue;
	}
	else if (offset < -offsetRange) {
		offset = -offsetRange;
		offsetValue = -offsetValue;
	}


	if (Zoffset > ZoffsetRange) {
		Zoffset = ZoffsetRange;
		ZoffsetValue = -ZoffsetValue;
	}
	else if (Zoffset < -ZoffsetRange) {
		Zoffset = -ZoffsetRange;
		ZoffsetValue = -ZoffsetValue;
	}

	offset += offsetValue * dt;
	//std::cout << offset << std::endl;
	glBindVertexArray(VAO);
	m_shader->use();
	modelMat = glm::mat4(1.0f);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 invViewMat = glm::inverse(camera.GetViewMatrix());
	glm::vec3 transpot = glm::vec3(0.15f, -0.15f, -0.5f);

	//model = invViewMat * translation * rotation * scaleMat;
	model = invViewMat;
	model = glm::translate(model, glm::vec3(transpot.x,transpot.y+offset,transpot.z+Zoffset));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.08f));

	viewMat = camera.GetViewMatrix();
	projectionMat = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.01f, 250.0f);


	m_shader->setUniform4m("modelMat", model);
	m_shader->setUniform4m("viewMat", viewMat);
	m_shader->setUniform4m("projectMat", projectionMat);

	//Set Directional Light
	m_shader->setUniform3f("lightD.pos", lightD->Position);
	m_shader->setUniform3f("lightD.color", lightD->Color);
	m_shader->setUniform3f("lightD.dirToLight", lightD->Direction);

	//Set Spot Light
	m_shader->setUniform3f("lightS.pos", camera.Position);
	m_shader->setUniform3f("lightS.color", lightS->Color);
	m_shader->setUniform3f("lightS.dirToLight", lightS->Direction);
	m_shader->setUniform1f("lightS.cosPhyInner", lightS->cosPhyInner);
	m_shader->setUniform1f("lightS.cosPhyOutter", lightS->cosPhyOutter);


	m_shader->setUniform3f("cameraPos", camera.Position);
	//treeShader->setUniform4f("plane", clip);

	//Set Meterial -> Testure
	m_shader->setUniform3f("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
	m_shader->setUniform1i("material.diffuse", 0);
	m_shader->setUniform1i("material.specular", 1);

	m_shader->setUniform1f("material.shininess", 32.0f);
	m_shader->setUniform1i("FlashOn", FlashOn);

	//m_shader->setUniform4f("plane", clip);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, diffuse);
	//m_shader->setUniform1i("material.specular", 1);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, specular);
	//m_shader->setUniform1f("material.shininess", 64.0f);

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindVertexArray(0);
	//m_shader->stop();
	if (WeaponMod != 0) {
		gunModel->Draw(m_shader);
	}
	m_shader->stop();
	
}

void Weapon::Reload(float dt)
{
	if (amo == MaxAmo) {
		std::cout << " Full amo" << std::endl;
		return;
	}
	reloading = true;
	std::cout << " reloading can not shoot " << std::endl;
	currentReloadTime += 0.4 * dt;

	if (QuickReloadMod) {
		currentReloadTime = 0.5f;
		QuickReloadMod = false;
	}
	if (currentReloadTime >= totalReloadTime) {
		amo = MaxAmo;
		currentReloadTime = 0;
		reloading = false;
	}
}

void Weapon::QuickReload(float dt)
{
	if (reloading == false && amo!=MaxAmo) {
		amo = 0;
		QuickReloadMod = true;
		reloading = true;
		Reload(dt);
	}
}

void Weapon::IniteModel(Model* gModel)
{
	m_shader = new Shader("Modelvert.vert", "Modelfrag.frag");
	gunModel = gModel;
}
