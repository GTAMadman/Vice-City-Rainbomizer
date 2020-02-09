#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"

class Colours : Functions
{
public:
	static void Initialise();
private:
	static void* __fastcall RandomizeColours(CRGBA* colour, void* edx, int r, int g, int b, int a);
	static void* __fastcall RandomizeArmourColours(CRGBA* colour, void* edx, int r, int g, int b, int a);
	static void __fastcall ChooseVehicleColour(CVehicleModelInfo* thisInfo, void* edx, int* prim, int* sec);
	static int RandomizeColourTable();
	static int GetColour(int pattern, int rgb);
	static CRGBA GetVibrantColour();
	struct Pattern
	{
		int ID;
		int colours[3];
	};
	static std::vector<Pattern> Patterns;
};