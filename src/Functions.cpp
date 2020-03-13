#include "Functions.h"

int* Functions::ms_numVehiclesLoaded = reinterpret_cast<int*>(0xA10858);
/* Initialised the random engine and given it a seed */
std::mt19937 Functions::rngEngine{ (unsigned int)time(0) };
char* Functions::currentThread = "noname";

void Functions::LoadModel(int modelID)
{
	if (CStreaming::ms_aInfoForModel[modelID].m_nLoadState != 1)
	{
		CStreaming::RequestModel(modelID, 1);
		CStreaming::LoadAllRequestedModels(false);
	}
}
int Functions::RandomNumber(unsigned int min, unsigned int max)
{
	std::uniform_int_distribution<int> random(min, max);
	return random(rngEngine);
}
char* Functions::GetThreadName()
{
	return currentThread;
}
void Functions::SetThreadName(char* thread)
{
	currentThread = thread;
}
bool Functions::DoCoordinatesMatch(int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (x1 == x2 && y1 == y2 && z1 == z2)
		return true;
	return false;
}
bool Functions::IsModelLoaded(int modelID)
{
	if (CStreaming::ms_aInfoForModel[modelID].m_nLoadState == 1)
		return true;
	return false;
}
void __fastcall Functions::StartMission(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	SetThreadName(script->m_szName);
}