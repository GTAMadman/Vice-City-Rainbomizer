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
	static char* currentThread;
public:
	static int RandomNumber(unsigned int min, unsigned int max);
	static void LoadModel(int modelID);
	static char* GetThreadName();
	static void SetThreadName(char* thread);
	static bool DoCoordinatesMatch(int x1, int y1, int z1, int x2, int y2, int z2);
	static void __fastcall StartMission(CRunningScript* script, void* edx, int* arg0, short count);
};