#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "CWeaponInfo.h"
#include "CProjectileInfo.h"
#include "CDarkel.h"

class Weapons : Functions
{
public:
	static void Initialise();
private:
	static std::vector<int> WeaponGroups[8];
	static int __fastcall GiveRandomizedWeapon(CPed* ped, void* edx, eWeaponType weapon, int ammo, bool likeUnused);
	static void __fastcall SetCurrentWeapon(CPed* ped, void* edx, eWeaponType weapon);
	static void __fastcall SetPlayerCurrentWeapon(CRunningScript* script, void* edx, int* arg0, short count);
	static CEntity* __fastcall PutPedOnTurretModeWithWeapon(CPed* ped, void* edx, CEntity* entity,
		CVector offset, short position, float angle, eWeaponType weapon);
	static void __fastcall GivePlayerRandomWeaponForRange(CPed* ped, void* edx, eWeaponType weapon, int ammo);
	static void __fastcall FixWeaponCheckForRange(CRunningScript* script, void* edx, int* arg0, short count);
	static void GiveRandomWeaponForRampage(eWeaponType weapon, int time, short kill, int modelId0, unsigned short* text,
		int modelId2, int modelId3, int modelId4, bool standardSound, bool needHeadshot);
	static void FixDriveByRampages(CPed* ped, eWeaponType weapon, bool arg2);
	static void HandleEndOfRampages();
	static int ProcessWeaponChange(int weapon, bool turret_mode, bool is_rampage, std::string thread);
	static bool IsBlacklistedWeapon(int weaponID);
	static void FixPedsWithRPG(CProjectileInfo* projectile);
	struct Pattern
	{
		int weapon = 0;
		bool turret_mode = false;
		bool is_rampage = false;
		std::vector<int> allowed = {};
		std::string thread = "";
	};
	inline static int player_weapon = -1;
	inline static bool DriveByRampageActive = false;
	static std::vector<Pattern> Patterns;
	static void InitialiseWeaponPatterns();
};