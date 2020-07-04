#include "Autosave.h"

bool Autosave::ShouldSave = false;
void __fastcall Autosave::RequestAutosave(CRunningScript* script, void* edx, int opcode)
{
	ProcessCommands0to99(script, opcode);

	if (opcode == 78 && script->m_bIsMission && ShouldSave)
	{
		int slot = Config::autosave.slot;
		bool inVehicle = FindPlayerPed()->m_bInVehicle;

		script->m_bIsActive = false;

		if (FindPlayerVehicle())
			FindPlayerPed()->m_bInVehicle = false;

		char* file = MakeValidSaveName(slot - 1);
		int handle = CFileMgr::OpenFile(file, "wb");
		
		GenericSave(handle);
		CFileMgr::CloseFile(handle);

		ShouldSave = false;
		FindPlayerPed()->m_bInVehicle = inVehicle;
	}
}
void __fastcall Autosave::SetTotalNumberMissions(CRunningScript* thisScript, void* edx, int* arg0, short count)
{
	thisScript->CollectParameters(arg0, count);
	ShouldSave = true;
}
char* Autosave::MakeValidSaveName(int slot)
{
	return plugin::CallAndReturnDynGlobal<char*>(0x61A630, slot);
}
void Autosave::GenericSave(int fileHandle)
{
	plugin::CallAndReturn<int, 0x61C420>(fileHandle);
}
char Autosave::ProcessCommands0to99(CRunningScript* script, int opcode)
{
	return plugin::CallMethodAndReturn<char, 0x44B400>(script, opcode);
}
void Autosave::Initialise()
{
	if (Config::autosave.Enabled)
	{
		plugin::patch::RedirectCall(0x44FC32, RequestAutosave);
		plugin::patch::RedirectCall(0x456992, SetTotalNumberMissions);
	}
}