#pragma once
#include<iostream>
class Player
{
public:
	Player();
	~Player() = default;
	float hp;
	float atk;
	float atkDuration,atkDurationMax;
	float GetAmo() { return amo; };
	int GetWeapon() { return WeaponMod; };
	void SetAtk(float n);
	void beAttack(float damage);
	void AmoCheck();
	void Reload(float dt);
	void QuickReload(float dt);
	bool ReloadCheck();
	void CloseFight();
	bool QuickReloadMod;

	void SwitchWeapon(int n);

private:
	bool WeaponSwitching;
	int WeaponMod;
	float amo;
	float anotherAmo;
	float MaxAmo;
	float currentReloadTime, totalReloadTime;
	bool reloading;
};

