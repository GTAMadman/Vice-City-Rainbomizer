#include "Weapons.h"

std::vector<Weapons::Pattern> Weapons::Patterns;
std::vector<int> Weapons::WeaponGroups[8] =
{
	{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 34, 36}, // Melee
	{12, 13, 14, 15, 16}, // Projectiles
	{17, 18}, // Pistols
	{19, 20, 21}, // Shotguns
	{22, 23, 24, 25}, // Submachine guns
	{26, 27}, // Assault rifles
	{28, 29}, // Sniper rifles
	{30, 31, 32, 33, 35} // Heavy weapons
};

int __fastcall Weapons::GiveRandomizedWeapon(CPed* ped, void* edx, eWeaponType weapon, int ammo, bool likeUnused)
{
	int origSlot = CWeaponInfo::GetWeaponInfo((eWeaponType)weapon)->m_WeaponSlot;

	if (!Config::weapons.randomizePlayerWeapons && (ped == FindPlayerPed()) || 
		ped->m_nModelIndex == -1 || weapon == 13 || weapon == 34)
	{
		ped->GiveWeapon(weapon, ammo, likeUnused);
		if (ped == FindPlayerPed())
			player_weapon = weapon;

		return origSlot;
	}

	int newWeapon = ProcessWeaponChange(weapon, false, false, GetMissionThread());
	int weaponModel = CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_nModelId;

	// Load the weapon model before setting it
	LoadModel(weaponModel);
	if (!IsModelLoaded(weaponModel))
		newWeapon = weapon;

	int newSlot = CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_WeaponSlot;

	if (ped == FindPlayerPed())
	{
		ped->GiveWeapon((eWeaponType)newWeapon, ammo, likeUnused);
		player_weapon = newWeapon;
		return newSlot;
	}

	CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_WeaponSlot = origSlot;

	ped->GiveWeapon((eWeaponType)newWeapon, ammo, likeUnused);
	ped->m_nActiveWeaponSlot = origSlot;

	CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_WeaponSlot = newSlot;
	return newWeapon;
}
void __fastcall Weapons::SetCurrentWeapon(CPed* ped, void* edx, eWeaponType weapon)
{
	if (ped->m_nModelIndex == -1 || IsPolicePedModel(ped->m_nModelIndex) || ped == FindPlayerPed())
	{
		int newSlot = CWeaponInfo::GetWeaponInfo(weapon)->m_WeaponSlot;
		ped->SetCurrentWeapon(newSlot);
	}
	else
		ped->SetCurrentWeapon(ped->m_nActiveWeaponSlot);
}
CEntity* __fastcall Weapons::PutPedOnTurretModeWithWeapon(CPed* ped, void* edx, CEntity* entity, CVector offset,
	short position, float angle, eWeaponType weapon)
{
	if (!Config::weapons.randomizePlayerWeapons && ped == FindPlayerPed())
		return ped->AttachPedToEntity(entity, offset, position, angle, weapon);

	int newWeapon = ProcessWeaponChange(weapon, true, false, GetMissionThread());
	int weaponModel = CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_nModelId;

	if (IsMission("bankjo2") || IsMission("range"))
		newWeapon = 0;

	LoadModel(weaponModel);
	if (!IsModelLoaded(weaponModel))
		newWeapon = weapon;

	return ped->AttachPedToEntity(entity, offset, position, angle, (eWeaponType)newWeapon);
}
void __fastcall Weapons::SetPlayerCurrentWeapon(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int& weapon = CTheScripts::ScriptParams[1].iParam;

	if (weapon != 13 && weapon != 34)
	{
		if (player_weapon > -1)
			weapon = player_weapon;
		else
			weapon = 0;
	}
}
void __fastcall Weapons::GivePlayerRandomWeaponForRange(CPed* ped, void* edx, eWeaponType weapon, int ammo)
{
	int newWeapon = ProcessWeaponChange(weapon, false, false, GetMissionThread());
	if (!Config::weapons.randomizePlayerWeapons && ped == FindPlayerPed())
		newWeapon = weapon;

	int weaponModel = CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_nModelId;

	LoadModel(weaponModel);
	if (!IsModelLoaded(weaponModel))
		newWeapon = weapon;

	int slot = CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_WeaponSlot;

	player_weapon = newWeapon;
	ped->GiveWeapon((eWeaponType)newWeapon, ammo, false);
	ped->SetAmmo((eWeaponType)newWeapon, ammo);
	ped->SetCurrentWeapon(slot);
}
void __fastcall Weapons::FixWeaponCheckForRange(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);

	if (IsMission("bankjo2") || IsMission("range"))
		CTheScripts::ScriptParams[1].iParam = player_weapon;
}
void Weapons::GiveRandomWeaponForRampage(eWeaponType weapon, int time, short kill, int modelId0, unsigned short* text,
		int modelId2, int modelId3, int modelId4, bool standardSound, bool needHeadshot)
{
	int newWeapon = ProcessWeaponChange(weapon, false, true, GetMissionThread());
	int weaponModel = CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_nModelId;

	// Load the weapon model before setting it
	LoadModel(weaponModel);
	if (!IsModelLoaded(weaponModel))
		newWeapon = weapon;

	CDarkel::StartFrenzy((eWeaponType)newWeapon, time, kill, modelId0, text, modelId2, modelId3, modelId4, standardSound, needHeadshot);

	if (weapon == 42)
		DriveByRampageActive = true;
}
void Weapons::FixDriveByRampages(CPed* ped, eWeaponType weapon, bool arg2)
{
	if (DriveByRampageActive)
	{
		if (FindPlayerVehicle())
			CDarkel::KillsNeeded--;

		CStats::PeopleKilledByPlayer++;
	}
	if (!DriveByRampageActive)
		CDarkel::RegisterKillByPlayer(ped, weapon, arg2);
}
void Weapons::HandleEndOfRampages()
{
	DriveByRampageActive = false;
	CDarkel::DealWithWeaponChangeAtEndOfFrenzy();
}
bool Weapons::IsBlacklistedWeapon(int weaponID)
{
	switch (weaponID)
	{
	case 16:
		if (Config::weapons.RocketEnabled)
			return false;
		return true;
	case 14:
		if (Config::weapons.tearGasEnabled)
			return false;
		return true;
	case 13:
	case 35:
		return true;
	}
	return false;
}
void Weapons::FixPedsWithRPG(CProjectileInfo* projectile)
{
	if (projectile->ms_apProjectile[0].pSource)
	{
		projectile->Update();
		return;
	}
	projectile->RemoveAllProjectiles();
}
void Weapons::InitialiseWeaponPatterns()
{
	// Phnom Penh '86 - Heli M60
	Pattern pattern = { .weapon = {32}, .turret_mode = {true}, .allowed = {18, 25, 
	26, 27, 32, 33}, .thread = {"baron2"} };
	Patterns.push_back(pattern);

	// Supply & Demand
	pattern = { .weapon = {27}, .turret_mode = {true}, .allowed = {27, 17, 18, 
	22, 23, 24, 25, 26, 32, 33}, .thread = {"baron4"} };
	Patterns.push_back(pattern);

	// Martha's Mug Shot - Camera
	pattern = { .weapon = {36}, .allowed = {36}, .thread = {"porno3"} };
	Patterns.push_back(pattern);

	// Dirty Lickin's - Sniper
	pattern = { .weapon = {28}, .allowed = {28, 29, 18, 30, 25, 26, 27, 32, 33}, .thread = {"hait3"} };
	Patterns.push_back(pattern);

	// The Shootist - Pistol
	pattern = { .weapon = {17}, .allowed = {17, 18, 22, 23, 24, 25, 26, 27, 32, 33}, .thread = {"bankjo2"} };
	Patterns.push_back(pattern);

	// Shooting Range - Pistol
	pattern = { .weapon = {17}, .allowed = {17, 18, 22, 23, 24, 25, 26, 27, 32, 33}, .thread = {"range"} };
	Patterns.push_back(pattern);

	// Naval Engagement - Ruger
	pattern = { .weapon = {27}, .allowed = {27, 12, 15, 17, 18, 19, 20, 21, 22, 23, 
	24, 25, 26, 30, 31, 32, 33, 28, 29}, .thread = {"cuban3"} };
	Patterns.push_back(pattern);


	/* RAMPAGES */

	// Run-Over
	pattern = { .weapon = {40}, .is_rampage = {true}, .allowed = {40} };
	Patterns.push_back(pattern);

	// Drive-By
	pattern = { .weapon = {42}, .is_rampage = {true}, .allowed = {22, 23, 24, 25} };
	Patterns.push_back(pattern);

	// M4
	pattern = { .weapon = {26}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Katana
	pattern = { .weapon = {10}, .is_rampage = {true}, .allowed = {10, 2, 3, 4, 5, 6,
	7, 8, 9, 11, 12, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Chainsaw
	pattern = { .weapon = {11}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// RPG
	pattern = { .weapon = {30}, .is_rampage = {true}, .allowed = {12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Grenades
	pattern = { .weapon = {12}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Molotovs
	pattern = { .weapon = {15}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Sniper
	pattern = { .weapon = {28}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Lazer Scope
	pattern = { .weapon = {29}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Shotgun
	pattern = { .weapon = {19}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// MP5
	pattern = { .weapon = {25}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Spaz Shotgun
	pattern = { .weapon = {20}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Python
	pattern = { .weapon = {18}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Minigun
	pattern = { .weapon = {33}, .is_rampage = {true}, .allowed = {12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Flamethrower
	pattern = { .weapon = {31}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// M60
	pattern = { .weapon = {32}, .is_rampage = {true}, . allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Tec9
	pattern = { .weapon = {22}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);

	// Ruger
	pattern = { .weapon = {27}, .is_rampage = {true}, .allowed = {11, 12, 15, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 26, 27, 30, 31, 32, 33, 28, 29} };
	Patterns.push_back(pattern);
}
int Weapons::ProcessWeaponChange(int weapon, bool turret_mode, bool is_rampage, std::string thread)
{
	if (Config::weapons.forcedWeapon >= 1 && Config::weapons.forcedWeapon <= 36)
		return Config::weapons.forcedWeapon;

	for (int i = 0; i < Patterns.size(); i++)
	{
		int index = i;
		std::vector<int> weapons;

		if (Patterns[index].weapon == weapon)
		{
			// Rampages Check
			if (Patterns[index].is_rampage)
				weapons = Patterns[index].allowed;

			// Thread & Turret Mode Check
			if (Patterns[index].thread != "" || Patterns[index].thread != "noname")
			{
				if (Patterns[index].thread == thread && Patterns[index].turret_mode == turret_mode)
					weapons = Patterns[index].allowed;
			}
			if (weapons.size() > 0)
				return weapons[RandomNumber(0, weapons.size() - 1)];
		}
	}

	// If there's no pattern

	if (Config::weapons.ReduceMeleeWeaponsEnabled)
	{
		int weaponGroup = RandomNumber(0, 7);
		while ((weapon = WeaponGroups[weaponGroup][RandomNumber(0, WeaponGroups[weaponGroup].size() - 1)], IsBlacklistedWeapon(weapon)));

		return weapon;
	}
	while ((weapon = RandomNumber(1, 36), IsBlacklistedWeapon(weapon)));
	return weapon;
}
void Weapons::Initialise()
{
	if (Config::weapons.Enabled)
	{
		for (int addr : {0x406CC7, 0x431C54, 0x452251, 0x4ED773, 0x4FFCCA,
			0x4FFD66, 0x50EE54, 0x50F24B, 0x5B897A, 0x5B89CE, 0x5D49B3, 
			0x60336B, 0x60343B, 0x603F64, 0x630090, 0x452206})
			plugin::patch::RedirectCall(addr, GiveRandomizedWeapon);

		for (int addr : {0x4440D5, 0x45241A, 0x452440, 0x4EB761, 0x452259,
			0x4EC234, 0x4EC2DB, 0x4ED63D, 0x4ED7DD, 0x4ED84E, 0x4ED8C8, 
			0x4EF461, 0x4FF688, 0x4FF70A, 0x4FF769, 0x4FF8F4, 0x50F254, 
			0x51C841, 0x51C85B, 0x520B30, 0x534472, 0x53B70B, 0x53B9C8, 
			0x5D49D3, 0x603493, 0x603FBC, 0x6300BB})
			plugin::patch::RedirectCall(addr, SetCurrentWeapon);

		plugin::patch::RedirectCall(0x60700E, PutPedOnTurretModeWithWeapon);
		plugin::patch::RedirectCall(0x631C11, PutPedOnTurretModeWithWeapon);
		plugin::patch::RedirectCall(0x4548A7, GivePlayerRandomWeaponForRange);
		plugin::patch::RedirectCall(0x608D3D, FixWeaponCheckForRange);

		if (Config::weapons.randomizePlayerWeapons)
		{
			plugin::patch::RedirectCall(0x452386, SetPlayerCurrentWeapon);
			plugin::patch::RedirectCall(0x63003E, SetPlayerCurrentWeapon);

			if (Config::weapons.randomizeRampageWeapons)
			{
				plugin::patch::RedirectCall(0x45772D, GiveRandomWeaponForRampage);
				plugin::patch::RedirectCall(0x526840, FixDriveByRampages);
				plugin::patch::RedirectCall(0x526B02, FixDriveByRampages);
				plugin::patch::RedirectCall(0x429FB4, HandleEndOfRampages);
				plugin::patch::RedirectCall(0x42A6A5, HandleEndOfRampages);
				plugin::patch::RedirectCall(0x42A770, HandleEndOfRampages);
			}
		}
		plugin::patch::RedirectCall(0x5D4DBA, FixPedsWithRPG);

		if (Patterns.size() == 0)
			InitialiseWeaponPatterns();
	}
}