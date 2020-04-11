#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "CWeaponInfo.h"
#include "CTheScripts.h"
#include "CRunningScript.h"

class Weapons : Functions
{
public:
	static void Initialise();
private:
	static std::vector<int> WeaponGroups[];
	static int __fastcall GiveRandomizedWeapon(CPed* ped, void* edx, eWeaponType weapon, int ammo, bool likeUnused);
	static void __fastcall SetCurrentWeapon(CPed* ped, void* edx, eWeaponType weapon);
	static int GetRandomWeapon();
	static bool IsBlacklistedWeapon(int weaponID);
};
