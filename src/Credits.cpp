#include "Credits.h"
#include "CFont.h"

std::vector<wchar_t*> lead_developers = { L"GTAMadman", L"Parik" };
std::vector<wchar_t*> contributors = {L"123robot", L"Fryterp23"};
std::vector<wchar_t*> beta_testers = {L"HugoOne", L"VodCrack", L"SpeedyFolf", L"AdsSal"};

void Credits::PrintCredits(float x, float y, const wchar_t* text, int* position, float offset)
{
	plugin::Call<0x5445FF>(x, y, text, position, offset);
}
void Credits::PrintGroup(wchar_t* title, std::vector<wchar_t*> list, int* position, float offset)
{
	PrintCredits(1.0, 1.0, title, position, offset);

	for (auto item : list)
	{
		PrintCredits(0.9, 0.9, item, position, offset);
	}
	*position += 37.5;
}
void Credits::ModifyCredits(float x, float y, wchar_t* text, int* position, float offset)
{
	PrintCredits(1.1, 1.1, L"RAINBOMIZER", position, offset);
	*position += 37.5;

	PrintGroup(L"LEAD DEVELOPERS", lead_developers, position, offset);
	PrintGroup(L"CONTRIBUTORS", contributors, position, offset);
	PrintGroup(L"BETA TESTERS", beta_testers, position, offset);

	PrintCredits(x, y, text, position, offset);
}
void Credits::Initialise()
{
	if (Config::general.credits)
		plugin::patch::RedirectCall(0x544842, ModifyCredits);
}