#include "Clothes.h"

std::vector<std::string> Clothes::outfits = {"PLAYER", "PLAYER2", "PLAYER3", "PLAYER4", "PLAYER5",
"PLAYER6", "PLAYER7", "PLAYER8", "PLAYER9","PLAY11", "PLAY12", "PLAY10"};
void __fastcall Clothes::RandomizeClothes(CPed* ped, void* edx, const char* modelName)
{
	std::string newModel;

	// Two Bit Hit Fix
	if (GetThreadName() == std::string("ser3") && modelName == std::string("player5"))
	{
		ped->Undress(modelName);
		return;
	}
	newModel = outfits[RandomNumber(0, outfits.size() - 1)];
	ped->Undress(newModel.c_str());
}
void Clothes::Initialise()
{
	if (Config::clothes.Enabled)
	{
		for (int addr : {0x42BDDC, 0x42C1C7, 0x42C3C9, 0x45D35A})
			plugin::patch::RedirectCall(addr, RandomizeClothes);
	}
}