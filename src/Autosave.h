#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "CRunningScript.h"
#include "CFileMgr.h"

class Autosave : Functions
{
public:
	static void Initialise();
private:
	static void __fastcall SetTotalNumberMissions(CRunningScript* thisScript, void* edx, int* arg0, short count);
	static void __fastcall RequestAutosave(CRunningScript* script, void* edx, int opcode);
	static bool ShouldSave;
	static char* MakeValidSaveName(int slot);
	static void GenericSave(int fileHandle);
	static char ProcessCommands0to99(CRunningScript* script, int opcode);
};