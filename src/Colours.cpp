#include "Colours.h"

std::vector<Colours::Pattern> Colours::Patterns;
int Colours::GetColour(int pattern, int rgb)
{
	for (int i = 0; i < Patterns.size(); i++)
	{
		if (Patterns[i].ID == pattern)
		{
			if (rgb == 0)
				return Patterns[i].colours[0];
			if (rgb == 1)
				return Patterns[i].colours[1];
			if (rgb == 2)
				return Patterns[i].colours[2];
		}
	}
	return 0;
}
void* __fastcall Colours::RandomizeColours(CRGBA* colour, void* edx, int r, int g, int b, int a)
{
	int pattern = r + b + g;
	if (GetColour(pattern, 0) == 0)
	{
		if (Config::ColourRandomizer::vibrantOnlyEnabled)
		{
			CRGBA vibrantColour = GetVibrantColour();

			Pattern col = { r + g + b, {vibrantColour.r, vibrantColour.g, vibrantColour.b} };
			Patterns.push_back(col);
		}
		else
		{
			Pattern col = { r + g + b, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
			Patterns.push_back(col);
		}
	}

	if (r != g && g != b)
	{
		colour->r = GetColour(pattern, 0);
		colour->g = GetColour(pattern, 1);
		colour->b = GetColour(pattern, 2);
		colour->a = a;
	}
	else
	{
		colour->r = r;
		colour->g = g;
		colour->b = b;
		colour->a = a;
	}
	return colour;
}
/* Had to put armour into it's own hooked function due to some issues with it */
void* __fastcall Colours::RandomizeArmourColours(CRGBA* colour, void* edx, int r, int g, int b, int a)
{
	int pattern = r + b + g;
	if (Config::ColourRandomizer::vibrantOnlyEnabled)
	{
		CRGBA vibrantColour = GetVibrantColour();

		Pattern col = { r + g + b, {vibrantColour.r, vibrantColour.g, vibrantColour.b} };
		Patterns.push_back(col);
	}
	else
	{
		Pattern col = { r + g + b, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
		Patterns.push_back(col);
	}
	colour->r = GetColour(pattern, 0);
	colour->g = GetColour(pattern, 1);
	colour->b = GetColour(pattern, 2);
	colour->a = a;

	return colour;
}
CRGBA Colours::GetVibrantColour()
{
	CRGBA colour;

	int colours[3] = { 0, 0, 0 };
	int values[3] = { 255, 0, RandomNumber(1, 255) };
	std::vector<int> vec;

	for (int i = 0; i < 3; i++)
		vec.push_back(values[i]);

	for (int i = 0; i < 3; i++)
	{
		int rng = RandomNumber(0, vec.size() - 1);
		colours[i] = vec[rng];
		vec.erase(vec.begin() + rng);
	}

	colour.r = colours[0];
	colour.g = colours[1];
	colour.b = colours[2];
	colour.a = 255;

	return colour;
}
int Colours::RandomizeColourTable()
{
	CVehicleModelInfo::LoadVehicleColours();

	for (int i = 0; i < 95; i++)
	{
		CVehicleModelInfo::ms_colourTextureTable[i].r = RandomNumber(0, 255);
		CVehicleModelInfo::ms_colourTextureTable[i].g = RandomNumber(0, 255);
		CVehicleModelInfo::ms_colourTextureTable[i].b = RandomNumber(0, 255);
	}
	return 0;
}
void __fastcall Colours::ChooseVehicleColour(CVehicleModelInfo* thisInfo, void* edx, int* prim, int* sec)
{
	*prim = RandomNumber(0, 94);
	*sec = RandomNumber(0, 94);
}
void Colours::Initialise()
{
	if (Config::ColourRandomizer::vehicleEnabled)
	{
		// Choose Vehicle Colour
		plugin::patch::RedirectJump(0x579190, ChooseVehicleColour);
		plugin::patch::RedirectCall(0x4A4CBF, RandomizeColourTable);
	}
	if (Config::ColourRandomizer::textEnabled)
	{
		// Text Colours
		plugin::patch::RedirectJump(0x541570, RandomizeColours);
		plugin::patch::RedirectCall(0x558E2A, RandomizeArmourColours); // Armour value
		plugin::patch::RedirectCall(0x558F06, RandomizeArmourColours); // Armour icon
	}
}