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
	if (Config::ColourRandomizer::rainbowTextEnabled)
	{
		CRGBA rainbow = GetRainbowColour(r, g, b);
		if (r != g && g != b)
		{
			colour->r = rainbow.r;
			colour->g = rainbow.g;
			colour->b = rainbow.b;
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
	else
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
}
/* Had to put armour into it's own hooked function due to some issues with it */
void* __fastcall Colours::RandomizeArmourColours(CRGBA* colour, void* edx, int r, int g, int b, int a)
{
	if (Config::ColourRandomizer::rainbowTextEnabled)
	{
		CRGBA rainbow = GetRainbowColour(r, g, b);
		colour->r = rainbow.r;
		colour->g = rainbow.g;
		colour->b = rainbow.b;
		colour->a = a;
	}
	else
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
}
void __fastcall Colours::RandomizeMarkerColours(C3dMarker* marker)
{
	CRGBA original = marker->m_colour;

	marker->m_colour = GetRainbowColour(marker->m_colour.r, marker->m_colour.g, marker->m_colour.b);
	marker->m_colour.a = original.a;

	marker->Render();
	marker->m_colour = original;
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
CRGBA Colours::GetRainbowColour(int r, int g, int b)
{
	CRGBA colour;
	int colours[3];

	float time = 1000.0 * clock() / CLOCKS_PER_SEC;
	int hash = (r * 255 + g) * 255 + b;
	HSVtoRGB((int)(time / 10 + hash) % 360, 0.7, 0.7, colours);

	colour.r = colours[0];
	colour.g = colours[1];
	colour.b = colours[2];

	return colour;
}
void Colours::HSVtoRGB(int H, double S, double V, int output[3])
{
	double C = S * V;
	double X = C * (1 - std::abs(fmod(H / 60.0, 2) - 1));
	double m = V - C;
	double Rs, Gs, Bs;

	if (H >= 0 && H < 60)
	{
		Rs = C;
		Gs = X;
		Bs = 0;
	}
	else if (H >= 60 && H < 120)
	{
		Rs = X;
		Gs = C;
		Bs = 0;
	}
	else if (H >= 120 && H < 180)
	{
		Rs = 0;
		Gs = C;
		Bs = X;
	}
	else if (H >= 180 && H < 240)
	{
		Rs = 0;
		Gs = X;
		Bs = C;
	}
	else if (H >= 240 && H < 300)
	{
		Rs = X;
		Gs = 0;
		Bs = C;
	}
	else
	{
		Rs = C;
		Gs = 0;
		Bs = X;
	}

	output[0] = (Rs + m) * 255;
	output[1] = (Gs + m) * 255;
	output[2] = (Bs + m) * 255;
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
void __fastcall Colours::ScriptVehicleColourRandomizer(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);

	CTheScripts::ScriptParams[1].iParam = RandomNumber(0, 94);
	CTheScripts::ScriptParams[2].iParam = RandomNumber(0, 94);
}
void Colours::Initialise()
{
	if (Config::ColourRandomizer::vehicleEnabled)
	{
		// Choose Vehicle Colour
		plugin::patch::RedirectJump(0x579190, ChooseVehicleColour);
		plugin::patch::RedirectCall(0x4A4CBF, RandomizeColourTable);
		plugin::patch::RedirectCall(0x458337, ScriptVehicleColourRandomizer);
	}
	if (Config::ColourRandomizer::textEnabled)
	{
		// Text Colours
		plugin::patch::RedirectJump(0x541570, RandomizeColours);
		plugin::patch::RedirectCall(0x558E2A, RandomizeArmourColours); // Armour value
		plugin::patch::RedirectCall(0x558F06, RandomizeArmourColours); // Armour icon
	}
	if (Config::ColourRandomizer::markersEnabled)
		plugin::patch::RedirectCall(0x570BDF, RandomizeMarkerColours);
}