#pragma once
#include "plugin.h"
#include "CStreaming.h"
#include "CModelInfo.h"
#include "ModelInfo.h"
#include "CRunningScript.h"
#include <ctime>
#include <random>

class Functions
{
private:
	static std::mt19937 rngEngine;
	static int* ms_numVehiclesLoaded;
	static char* currentThread;
public:
	static int RandomNumber(int min, int max);
	static void LoadModel(int modelID);
	static char* GetThreadName();
	static void SetThreadName(char* thread);
	static bool DoCoordinatesMatch(int x1, int y1, int z1, int x2, int y2, int z2);
	static bool IsModelLoaded(int modelID);
	static int GetNumberOfVehiclesLoaded();
	static int GetRandomLoadedVehicle();
	static void __fastcall StartMission(CRunningScript* script, void* edx, int* arg0, short count);
};