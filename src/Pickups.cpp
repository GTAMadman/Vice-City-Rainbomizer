#include "Pickups.h"

std::vector<int> Pickups::allowed_pickups;
std::vector<int> Pickups::original_pickups = {259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270,
271, 272, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 292, 365, 
366, 367, 368, 375, 258, 335, 508};
int Pickups::RandomizePickups(CVector posn, int modelID, char arg3, int arg4, int arg5, bool arg6, char* msg)
{
	int newPickup = modelID;

	for (int i = 0; i < original_pickups.size(); i++)
	{
		if (modelID == original_pickups[i] || modelID == 291)
		{
			if (Config::pickups.usingSeed)
			{
				newPickup = allowed_pickups[GetRandomUsingCustomSeed(0, allowed_pickups.size() - 1)];
				break;
			}
			else
			{
				newPickup = allowed_pickups[RandomNumber(0, allowed_pickups.size() - 1)];
				break;
			}
		}
	}
	return CPickups::GenerateNewOne(posn, newPickup, arg3, arg4, arg5, arg6, msg);
}
bool Pickups::GiveMoneyForBriefcase(unsigned short model, int plrIndex)
{
	if (model == 335)
	{
		if (FindPlayerPed())
			FindPlayerPed()->GetPlayerInfoForThisPlayerPed()->m_nMoney += RandomNumber(1, 500);
	}
	return CPickups::GivePlayerGoodiesWithPickUpMI(model, plrIndex);
}
int Pickups::GetRandomUsingCustomSeed(int min, int max)
{
	static std::mt19937 pickupsEngine{ std::hash<std::string>{}(Config::pickups.seed) };
	std::uniform_int_distribution<int> random(min, max);
	return random(pickupsEngine);
}
void Pickups::Initialise()
{
	if (Config::pickups.Enabled)
	{
		if (Config::pickups.weapons)
			for (int i = 0; i < 32; i++)
				allowed_pickups.push_back(original_pickups[i]);
		if (Config::pickups.health)
			allowed_pickups.push_back(366);
		if (Config::pickups.armour)
			allowed_pickups.push_back(368);
		if (Config::pickups.adrenaline)
			allowed_pickups.push_back(367);
		if (Config::pickups.bribes)
			allowed_pickups.push_back(375);
		if (Config::pickups.cellphone)
			allowed_pickups.push_back(258);
		if (Config::pickups.briefcase)
			allowed_pickups.push_back(335);
		if (Config::pickups.keycard)
			allowed_pickups.push_back(508);

		if (allowed_pickups.size() == 0)
			return;

		for (int addr : {0x4561CC, 0x4564E3, 0x457E99, 0x45B8BA, 
			0x60823C, 0x51C7C9, 0x62EAE3, 0x62EC20, 0x62FBD3})
			plugin::patch::RedirectCall(addr, RandomizePickups);

		if (Config::pickups.randomizePedDrops)
			plugin::patch::RedirectCall(0x43E143, RandomizePickups);

		if (Config::pickups.briefcaseMoney)
		{
			for (int addr : {0x440D6D, 0x440E7A, 0x441070})
				plugin::patch::RedirectCall(addr, GiveMoneyForBriefcase);
		}
	}
}