#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"
#include "ModelInfo.h"
#include "CHeli.h"
#include "CBike.h"
#include "CBoat.h"
#include "CRunningScript.h"
#include "CTheScripts.h"
#include "CCarCtrl.h"

class Script : Functions, ModelInfo
{
private:
	static void __fastcall ScriptVehicleRandomizer(CRunningScript* script, void* edx, int* arg0, short count);
	static void* __fastcall CreateRandomizedCab(CVehicle* vehicle, void* edx, int modelId, bool createdBy);
	static void __fastcall FixForcedPlayerVehicleType(CRunningScript* script, void* edx, int* arg0, short count);
	static void __fastcall FixForcedPedVehicleType(CRunningScript* script, void* edx, int* arg0, short count);
	static void __fastcall FixTrojanVoodooForcedVehicle(CRunningScript* script, void* edx, int* arg0, short count);
	static void* __fastcall OpenBootFix(CAutomobile* vehicle);
	static void __fastcall FixBombsAwayVan(CRunningScript* script, void* edx, int* arg0, short count);
	static void FixBombsAwayBombPosition(CPhysical* phy1, CPhysical* phy2, CVector offset);
	static void __fastcall FixFrozenLoadingScreens(CRunningScript* script, void* edx, char flag);
	static bool FixWaterLevelCrash(float fX, float fY, float fZ, float* pfOutLevel, bool bDontCheckZ);
	static void AlloyWheelsFix(int modelID);
	struct Pattern
	{
		int vehicle = 0;
		std::string gVehicle = "";
		std::vector<int> allowed = {};
		std::vector<int> denied = {};
		std::vector<std::string> allowedType = {};
		int coords[3] = { 0, 0, 0 };
		int move[3] = { 0, 0, 0 };
		std::string thread = "";
		bool door_check = false;
		std::string moveType[3] = { "", "", ""};
		int chosen = 0; // Mainly used for moving specific vehicle types
	};
	static std::vector<int> ProcessVehicleTypes(Pattern pattern);
	static std::vector<int> AlloyWheelsVehicles;
public:
	static void Initialise();
	static int ProcessScriptVehicleChange(int origModel, int x, int y, int z, std::string thread);
	static CVector CheckPatternForMovePosition(int origModel, int x, int y, int z);
	static std::vector<Pattern> Patterns;
	static void InitialisePatterns();
};