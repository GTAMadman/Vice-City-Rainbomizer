#include "Colours.h"

std::vector<Colours::Pattern> Colours::Patterns;
std::vector<Colours::Pattern> Colours::PickupPatterns;
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
int Colours::GetPickupsColour(int pattern, int rgb)
{
	for (int i = 0; i < PickupPatterns.size(); i++)
	{
		if (PickupPatterns[i].ID == pattern)
		{
			if (rgb == 0)
				return PickupPatterns[i].colours[0];
			if (rgb == 1)
				return PickupPatterns[i].colours[1];
			if (rgb == 2)
				return PickupPatterns[i].colours[2];
		}
	}
	return 0;
}
void* __fastcall Colours::RandomizeColours(CRGBA* colour, void* edx, int r, int g, int b, int a)
{
	if (Config::colours.rainbowTextEnabled)
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
		int pattern = r + g + b;
		if (GetColour(pattern, 0) == 0)
		{
			if (Config::colours.vibrantOnlyEnabled)
			{
				CRGBA vibrantColour = GetVibrantColour();

				Pattern col = { pattern, {vibrantColour.r, vibrantColour.g, vibrantColour.b} };
				Patterns.push_back(col);
			}
			else
			{
				Pattern col = { pattern, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
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
	if (Config::colours.rainbowTextEnabled)
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
		if (Config::colours.vibrantOnlyEnabled)
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

	if (Config::colours.staticMarkerColours)
	{
		int pattern = marker->m_colour.r + marker->m_colour.g + marker->m_colour.b;
		if (GetColour(pattern, 0) == 0)
		{
			Pattern obj = { pattern, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
			Patterns.push_back(obj);
		}
		marker->m_colour.r = GetColour(pattern, 0);
		marker->m_colour.g = GetColour(pattern, 1);
		marker->m_colour.b = GetColour(pattern, 2);
	}
	else
	{
		marker->m_colour = GetRainbowColour(marker->m_colour.r, marker->m_colour.g, marker->m_colour.b);
		marker->m_colour.a = original.a;
	}

	marker->Render();
	marker->m_colour = original;
}
void Colours::RandomizePickupColours(int coronaID, char r, char g, char b, char a, CVector const& posn, float radius,
	float farClip, char arg8, char flare, char refl, char arg11, char arg12, float normalAngle, bool arg14, float arg15)
{
	CRGBA colour;
	if (Config::colours.staticPickupColours)
	{
		int pattern = coronaID;
		if (GetColour(pattern, 0) == 0)
		{
			Pattern obj = { pattern, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
			Patterns.push_back(obj);
		}
		colour.r = GetColour(pattern, 0);
		colour.g = GetColour(pattern, 1);
		colour.b = GetColour(pattern, 2);
	}
	else
	{
		int pattern = coronaID;
		if (GetPickupsColour(pattern, 0) == 0)
		{
			Pattern col = { pattern, {r, g, b} };
			PickupPatterns.push_back(col);
		}
		int origR = GetPickupsColour(pattern, 0);
		int origG = GetPickupsColour(pattern, 1);
		int origB = GetPickupsColour(pattern, 2);

		colour = GetRainbowColour(origR, origG, origB);
	}

	CCoronas::RegisterCorona(coronaID, colour.r, colour.g, colour.b, a, posn, radius, farClip, arg8, flare,
		refl, arg11, arg12, normalAngle, arg14, arg15);
}
void Colours::RandomizeMiscColours(int coronaID, char r, char g, char b, char a, CVector const& posn, float radius,
	float farClip, char arg8, char flare, char refl, char arg11, char arg12, float normalAngle, bool arg14, float arg15)
{
	CRGBA colour;
	if (Config::colours.staticLazerScopeColours)
	{
		int pattern = coronaID;
		if (GetColour(pattern, 0) == 0)
		{
			Pattern obj = { pattern, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
			Patterns.push_back(obj);
		}
		colour.r = GetColour(pattern, 0);
		colour.g = GetColour(pattern, 1);
		colour.b = GetColour(pattern, 2);
	}
	else
	{
		static int origR = 200;
		static int origG = 0;
		static int origB = 0;

		colour = GetRainbowColour(origR, origG, origB);
	}

	CCoronas::RegisterCorona(coronaID, colour.r, colour.g, colour.b, a, posn, radius, farClip, arg8, flare,
		refl, arg11, arg12, normalAngle, arg14, arg15);
}
void Colours::RandomizeExplosionColours(int coronaID, char r, char g, char b, char a, CVector const& posn, float radius,
	float farClip, RwTexture* texture, char flare, char refl, char arg11, char arg12, float normalAngle, bool arg14, float arg15)
{
	CRGBA colour;
	if (Config::colours.staticExplosionColours)
	{
		int pattern = coronaID;
		if (GetColour(pattern, 0) == 0)
		{
			Pattern obj = { pattern, {RandomNumber(1, 255), RandomNumber(1, 255), RandomNumber(1, 255)} };
			Patterns.push_back(obj);
		}
		colour.r = GetColour(pattern, 0);
		colour.g = GetColour(pattern, 1);
		colour.b = GetColour(pattern, 2);
	}
	else
	{
		colour = GetRainbowColour(r, g, b);
	}

	CCoronas::RegisterCorona(coronaID, colour.r, colour.g, colour.b, a, posn, radius, farClip, texture,
		flare, refl, arg11, arg12, normalAngle, arg14, arg15);
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
	if (Config::colours.vehicleEnabled)
	{
		plugin::patch::RedirectJump(0x579190, ChooseVehicleColour);
		plugin::patch::RedirectCall(0x4A4CBF, RandomizeColourTable);
		plugin::patch::RedirectCall(0x458337, ScriptVehicleColourRandomizer);
	}
	if (Config::colours.textEnabled)
	{
		plugin::patch::RedirectJump(0x541570, RandomizeColours);
		plugin::patch::RedirectCall(0x558E2A, RandomizeArmourColours); // Armour value
		plugin::patch::RedirectCall(0x558F06, RandomizeArmourColours); // Armour icon
	}
	if (Config::colours.markersEnabled)
	{
		plugin::patch::RedirectCall(0x570BDF, RandomizeMarkerColours); // Mission markers
		plugin::patch::RedirectCall(0x6313FF, RandomizeMiscColours); // Race markers
		plugin::patch::RedirectCall(0x458BEE, RandomizeMiscColours); // Race markers
	}
	if (Config::colours.pickupsEnabled)
	{
		for (int addr : {0x43EF94, 0x43F44B, 0x43F65A, 0x43F757, 0x43F8A8,
			0x43FF7D, 0x43FFCD, 0x43EA04, 0x43EC84})
			plugin::patch::RedirectCall(addr, RandomizePickupColours);
	}
	if (Config::colours.explosionsEnabled)
	{
		for (int addr : {0x5C5011, 0x5C5052, 0x5C5161, 0x5C51A2})
			plugin::patch::RedirectCall(addr, RandomizeExplosionColours);
	}
	if (Config::colours.lazerScopeEnabled)
		plugin::patch::RedirectCall(0x5CCB84, RandomizeMiscColours);
}