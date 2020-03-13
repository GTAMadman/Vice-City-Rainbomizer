#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"
#include "CRunningScript.h"
#include "CTheScripts.h"
#include "C3dMarkers.h"
#include "CCoronas.h"

class Colours : Functions
{
public:
	static void Initialise();
private:
	static void* __fastcall RandomizeColours(CRGBA* colour, void* edx, int r, int g, int b, int a);
	static void* __fastcall RandomizeArmourColours(CRGBA* colour, void* edx, int r, int g, int b, int a);
	static void __fastcall ChooseVehicleColour(CVehicleModelInfo* thisInfo, void* edx, int* prim, int* sec);
	static void __fastcall ScriptVehicleColourRandomizer(CRunningScript* script, void* edx, int* arg0, short count);
	static void __fastcall RandomizeMarkerColours(C3dMarker* marker);
	static int RandomizeColourTable();
	static int GetColour(int pattern, int rgb);
	static CRGBA GetVibrantColour();
	static CRGBA GetRainbowColour(int r, int g, int b);
	static void HSVtoRGB(int H, double S, double V, int output[3]);
	struct Pattern
	{
		int ID;
		int colours[3];
	};
	static std::vector<Pattern> Patterns;
};