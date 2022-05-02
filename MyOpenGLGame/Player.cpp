#include "Player.h"

Player::Player() :
	hp(100),
	atk(20),
	atkDuration(1.0f),
	atkDurationMax(1.0f),
	amo(10),
	anotherAmo(3),
	MaxAmo(10),
	reloading(false),
	WeaponSwitching(false),
	currentReloadTime(0),
	totalReloadTime(1.0f),
	QuickReloadMod(false),
	WeaponMod(1)
{
}

void Player::SetAtk(float n)
{
	atk = n;
}

void Player::beAttack(float damage)
{
	hp -= damage;
	//audio 
}

//check the amo,if amo is 0 ,this weapon need to reload
void Player::AmoCheck()
{
	atkDuration = 0;
	amo -- ;
	if (amo == 0) {
		reloading = true;
	}
}

//reload the weapon
void Player::Reload(float dt)
{
	reloading = true;
	//std::cout << " reloading" << std::endl;
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

//shorter reload time
void Player::QuickReload(float dt)
{
	if (reloading == false) {
		amo = 0;
		QuickReloadMod = true;
		reloading = true;
		Reload(dt);
	}
}


bool Player::ReloadCheck()
{
	return reloading? false:true;
}

void Player::CloseFight()
{

}

//Switching weapons
//different weapon has own data
//did not be used
void Player::SwitchWeapon(int n)
{
	WeaponSwitching = true;
	if (reloading == false) {
		if (n == 1) {
			//different gun have its own amo data
			//load the parent gun's amo data to anotherAmo
			if (WeaponMod == 2) {
				float a = amo;
				amo = anotherAmo;
				anotherAmo = a;
			}
			MaxAmo = 10;
			atkDurationMax = 1.0f;
			atkDuration = atkDurationMax;
			totalReloadTime = 1.0f;
			atk = 20.0f;

		}
		else if (n == 2) {
			if (WeaponMod == 1) {
				float a = amo;
				amo = anotherAmo;
				anotherAmo = a;
			}
			MaxAmo = 3;
			atkDurationMax = 2.0f;
			atkDuration = atkDurationMax;
			totalReloadTime = 1.3f;
			atk = 100.0f;
		}
		else  {
			MaxAmo = 999;
			atkDurationMax = 1.2f;
			atkDuration = atkDurationMax;
			totalReloadTime = 0;
			atk = 1.0f;
		}
	}
	
	WeaponMod = n;
	WeaponSwitching = false;
}

