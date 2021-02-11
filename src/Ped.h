#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "Player.h"
#include "CCivilianPed.h"
#include "CCopPed.h"

class Ped : Functions
{
public:
	static void Initialise();
	static std::vector<std::string> ped_models;
private:
	static void ChooseRandomPedToLoad(int modelId, int flags);
	static void* __fastcall RandomizeGenericPeds(CCivilianPed* ped, void* edx, ePedType type, int model);
	static void* __fastcall RandomizeAndFixStreetPeds(CCivilianPed* ped, void* edx, ePedType type, int model);
	static void* __fastcall RandomizeCopPeds(CCopPed* ped, void* edx, eCopType type, int arg1);
	static bool IsSpecialModel(int model);
	static int GetRandomGenericPedBasedOnModel(int model, bool ignoreChecks);
};