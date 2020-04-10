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
	std::array<std::vector<int>, 8> WeaponGroups =
	{
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 34, 36}, // Unarmed, BrassKnuckle, melee, Detonator, Camera
		{12, 13, 14, 15, 16}, // throwables
		{17, 18}, // pistols
		{19, 20, 21}, // shotguns
		{22, 23, 24, 25}, // submachine guns
		{26, 27}, // assault rifles
		{28, 29}, // sniper rifles
		{30, 31, 32, 33, 35} // heavy weapons
	};
	static int __fastcall GiveRandomizedWeapon(CPed* ped, void* edx, eWeaponType weapon, int ammo, bool likeUnused);
	static void __fastcall SetCurrentWeapon(CPed* ped, void* edx, eWeaponType weapon);
	static int GetRandomWeapon();
	static bool IsBlacklistedWeapon(int modelID);
};
