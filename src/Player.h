#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "CAnimBlendClumpData.h"
#include "CAnimBlendAssociation.h"
#include "common.h"
#include "rw/rwplcore.h"

class Player : Functions
{
public:
	static void Initialise();
	static std::vector<std::string> player_outfits;
	static std::vector<std::string> special_models;
private:
	static std::vector<std::string> all_outfits;
	static void __fastcall RandomizeOutfit(CPed* ped, void* edx, const char* modelName);
	static void __fastcall FixTwoBitHit(CRunningScript* script, void* edx, char flag);
	static void __fastcall FixAnimAfterModelChange(CPed* ped);
	static void GivePlayerRandomOutfit();
	static void RandomizeOutfitOnFade();
	static void ChangePlayerModel(const char* modelName);
	inline static CAnimBlendAssociation* association = nullptr;
};