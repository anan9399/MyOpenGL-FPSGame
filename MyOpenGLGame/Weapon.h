#pragma once
#include"Player.h"
#include"Raytest.h"
#include<irrKlang.h>

class Weapon
{
public:
	Weapon(Player* player);
	int *GetWeapon() { return &WeaponMod; };
	int *GetAmo() { return &amo; };
	int GetMaxAmo() { return MaxAmo; };
	void Upload(Camera camera, std::vector<Enermy*>enermies, irrklang::ISoundEngine* SoundEngine,Raytest* raytest, bool mouse_button, float dt);

	void AmoCheck();
	bool SwitchWeapon(Player* player, int mod, bool WeaponSwitching,float dt);
	void Draw(Camera& camera, LightDirectional* lightD, LightSpot* lightS, int FlashOn, bool mod, float dt);
	void Reload(float dt);
	void QuickReload(float dt);
	void IniteModel(Model* gModel);
	bool reloading, switching, runing;

private:
	Shader* m_shader;
	Model* gunModel;
	int VAO, VBO;
	
	int WeaponMod;
	int amo,MaxAmo,AnotherAmo;
	float currentReloadTime, totalReloadTime;
	float atkDuration, atkDurationMax;
	float SwitchDuration;
	bool QuickReloadMod;
	int diffuse, specular;
	float offset, offsetRange,offsetValue,Zoffset, ZoffsetRange, ZoffsetValue ;



	glm::mat4 modelMat;
	glm::mat4 viewMat;
	glm::mat4 projectionMat;

};

