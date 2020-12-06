#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"

class Clothes : Functions
{
public:
	static void Initialise();
private:
	static std::vector<std::string> outfits;
	static void __fastcall RandomizeClothes(CPed* ped, void* edx, const char* modelName);
};