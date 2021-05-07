#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "CPickups.h"

class Pickups : Functions
{
public:
	static void Initialise();
private:
	static int RandomizePickups(CVector posn, int modelID, char arg3, int arg4, int arg5, bool arg6, char* msg);
	static bool GiveMoneyForBriefcase(unsigned short model, int plrIndex);
	static int GetRandomUsingCustomSeed(int min, int max);
	static std::vector<int> original_pickups;
	static std::vector<int> allowed_pickups;
};