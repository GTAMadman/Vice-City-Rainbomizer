#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "CWeaponInfo.h"
#include "CRunningScript.h"
#include "CProjectileInfo.h"

class Weapons : Functions
{
public:
	static void Initialise();
private:
	static std::vector<int> WeaponGroups[8];
	static int __fastcall GiveRandomizedWeapon(CPed* ped, void* edx, eWeaponType weapon, int ammo, bool likeUnused);
	static void __fastcall SetCurrentWeapon(CPed* ped, void* edx, eWeaponType weapon);
	static bool IsBlacklistedWeapon(int weaponID);
	static int GetRandomWeapon();
	static void FixPedsWithRPG(CProjectileInfo* projectile);
};