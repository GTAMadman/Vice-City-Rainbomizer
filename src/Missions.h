#pragma once
#include "plugin.h"
#include <string>
#include <memory>
#include "Functions.h"
#include "Config.h"
#include "ModelInfo.h"
#include "CPedType.h"
#include "CFileMgr.h"
#include "CTheScripts.h"
#include "extensions\ScriptCommands.h"
#include "CGameLogic.h"
#include "CCamera.h"
#include "CWorld.h"
#include "CPickups.h"
#include <queue>
#include <map>

const int SIZE_MISSION_SCRIPT = 35000;
const int START_MISSIONS = 3;
const int END_MISSIONS = 74;
const int TOTAL_MISSIONS = END_MISSIONS - START_MISSIONS + 1;

class Missions : Functions
{
public:
	static void Initialise();

	struct MissionEndOffset
	{
		int Start;
		int End = -1;
	};

private:

	struct SaveStructure
	{
		char signature[12] = "RAINBOMIZER";
		unsigned int randomSeed;

		SaveStructure()
		{
			memcpy(signature, "RAINBOMIZER", 12);
		};
	};

	struct MissionOrder
	{
		int Missions[TOTAL_MISSIONS];

		MissionOrder() { Reset(); }

		inline int& operator [] (int index)
		{
			if (index < START_MISSIONS || index > END_MISSIONS)
				return Missions[START_MISSIONS];

			return Missions[index - START_MISSIONS];
		};

		void Reset();
	};

	inline static SaveStructure mSaveStructure;
	inline static MissionOrder mMissionOrder;

	inline static int mOriginalMission = -1;
	inline static int mRandomizedMission = -1;
	inline static bool mStoreNextScript = false;
	inline static bool mScriptReplaced = false;
	inline static CRunningScript* mRandomizedScript = nullptr;

	inline static std::vector<MissionEndOffset> mPostReplaceEndOffsets;
	inline static std::vector<MissionEndOffset> mPreReplaceEndOffsets;

	inline static std::unique_ptr<unsigned char[]> mTempMissionData;
	inline static std::unique_ptr<unsigned int[]> mLocalVariables;

	static void TeleportPlayerAfterMission();
	static void InitShuffledMissionOrder(SaveStructure*);

	static bool ShouldJump(CRunningScript*);

	static void MoveScriptToOriginalOffset(CRunningScript*);
	static void RestoreOriginalScriptForCleanup();

	static void __fastcall RandomizeMissionToStart(CRunningScript* script, void* edx, int* arg0, short count);
	static CRunningScript* StoreRandomizedScript(uint32_t ip);
	static char __fastcall JumpOnMissionEnd(CRunningScript*);

	static int GetRandomMission();

	static bool ProcessPreReplaceMissionEndOffsets(CRunningScript*, short opcode);
	static bool ProcessPostReplaceMissionEndOffsets(CRunningScript*, uint16_t& opcode);
	static void HandleEndThreadOpcode(CRunningScript*, short opcode);

	static void LoadMissionData(uint8_t* data, uint32_t size);
	static void SaveMissionData(uint8_t* data, uint32_t& size);

	static bool IsBlacklistedMission(int missionId);
	static eLevelName GetIslandFromMissionStart(int mission);
	static eLevelName GetIslandFromMissionEnd(int mission);
	static void __fastcall FixPayphoneMissions(CPed* ped);
	static void __fastcall KeepYachtAfterAHoD(CRunningScript* script, void* edx, int* arg0, short count);
	static void* __fastcall LoadCortezCutsceneArea(CPools* pool, void* edx, int index);
	static void __fastcall SpawnKaufmanForTaxiMissions(CPlayerInfo* player, void* edx, bool safe);
	static void FixStartOfMissions();
	static bool IsRubOutCompleted();
	static bool IsPayphoneMission(int mission);
	static bool IsFinalAssetMission(int mission);
	static eInterior GetInteriorBasedOnMissionStart(int mission);
	static eInterior GetInteriorBasedOnMissionEnd(int mission);
	static void SetInteriorGlobalVars(int mansion, int mall, int malibu, int shooting_range);
	static void FixCapTheCollector();
	static void ResetAssets();
	static void FixTaxiDestinations(float x, float y, float z, float angle);
	static void ResetKaufmanCabs();
	static void FixStartingKaufmanMissions();
	static void RemoveBridgesAndObjects(CEntity* entity);
	static void __fastcall SetPosAndAngleForStarIslandGateOnNewGame(CRunningScript* script, void* edx, int* arg0, short count);
	static void RebuildNonExistingObjects(unsigned char* buffer, unsigned int size);
	static void __fastcall RemoveCarCubes(CPathFind* path, void* edx, float x1, float y1,
		float z1, float x2, float y2, float z2, char a3);
	static void __fastcall RemovePedCubes(CPathFind* path, void* edx, float x1, float y1,
		float z1, float x2, float y2, float z2, char a3);
	static void __fastcall ReplaceFactoryWithFixedModels(CCamera* camera);
	static void __fastcall ReplaceBuildings(CBuilding* building, void* edx, int modelId);
	static void HandleUnloadedAreasAndDoors(CVector* pos);
	static void RemoveDoorsForKYFC(CEntity* entity);
	static int ReplaceObject(int modelID);
	static void SetPositionForStudioGates(CEntity& object);
	static bool ShouldRemoveObject(int modelID);
	static bool ShouldRemoveCarAndPedCube(int x1, int x2);
	static void SetPosAndAngleForStarIslandGate();
	inline static bool ShouldDestroyFactory;
	inline static bool ShouldOpenMansionDoors;
	inline static bool ShouldCloseMansionDoors;
	static void RebuildHaitianFactory();
	static void DestroyHaitianFactory();
	static void OpenMansionDoors();
	static void CloseMansionDoors(bool isKYFC);
	static void FixOutsideInterior(eLevelName level);
};