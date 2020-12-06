#pragma once
#include "plugin.h"
#include "Config.h"

class Credits
{
public:
	static void Initialise();
private:
	static void ModifyCredits(float x, float y, wchar_t* text, int* position, float offset);
	static void PrintCredits(float x, float y, const wchar_t* text, int* position, float offset);
	static void PrintGroup(wchar_t* title, std::vector<wchar_t*> list, int* position, float offset);
};