#include "Missions.h"

std::map<int, std::vector<Missions::MissionEndOffset>> gMissionEndOffsets
= { {3, {{12177}}},
{4, {{13332}}},
{5, {{8066}}},
{6, {{9049}}},
{7, {{8887}}},
{8, {{9912}}},
{9, {{26195}}},
{10, {{28424}}},
{11, {{30843}}},
{12, {{8656}}},
{13, {{13929}}},
{14, {{7671}}},
{15, {{10301}}},
{16, {{11872, 11887}, {11909}}},
{17, {{7704}}},
{18, {{9816}}},
{19, {{21004}}},
{20, {{4997}}},
{21, {{7652}}},
{22, {{27114, 27177}, {27191}}},
{23, {{7448, 7478}, {7539, 7565}, {7632}}},
{24, {{22590, 22624}, {23461}}},
{25, {{12345}}},
{26, {{6489, 6876}, {7013}}},
{27, {{11183}}},
{28, {{7457}}},
{29, {{9251}}},
{30, {{10911}}},
{31, {{5850}}},
{32, {{12066}}},
{33, {{11209}}},
{34, {{6520}}},
{35, {{18941}}},
{51, {{9176}}},
{52, {{24653}}},
{53, {{7000, 7030}, {7228, 7254}, {7321}}},
{54, {{1911, 1936}, {2073}}},
{55, {{5002}}},
{56, {{10682}}},
{57, {{16564}}},
{58, {{11515}}},
{59, {{20121, 20160}, {20219}}},
{60, {{5519}}},
{61, {{17571}}},
{62, {{4031}}},
{63, {{7151}}},
{64, {{9504}}},
{65, {{9225}}},
{67, {{1841}}},
{68, {{4088}}},
{69, {{6637}}},
{70, {{8263}}},
{71, {{12394, 12411}, {12416}}},
{72, {{3925}}},
{73, {{1613}}},
{74, {{5001}}} };

std::map<int, CVector> gMissionEndCoords
= { {2, {223.1, -1276.7, 12.0793}}, {3, {102.643, -1479.55, 10.2684}},
{4, {240.836, -1278.28, 10.9015}}, {5, {202.7, -1016.4, 10.4318}},
{6, {289.57, -318.226, 11.9591}}, {7, {490.917, 29.9993, 10.9015}},
{8, {-232.573, -1359.2, 8.11297}}, {9, {460.668, -488.894, 11.0712}},
{10, {-1062.8, -476.156, 11.0845}},  {11, {11.1149, 868.886, 10.9252}},
{12, {34.018, 1074.25, 12.8185}},  {13, {-378.495, -537.259, 17.283}},
{14, {-379.4846, -646.2098, 10.4131}},  {15, {-379.4846, -646.2098, 10.4131}},
{16, {-378.381, -588.85, 25.3228}}, {17, {-825.216, 1164.76, 10.9988}},
{18, {133.527, 568.761, 15.4792}},  {19, {226.074, -352.412, 10.912}},
{20, {-969.996, 426.071, 10.8066}},  {21, {-829.21, -900.18, 11.0895}},
{22, {-662.608, 1232.26, 11.0985}}, {23, {513.783, -73.9407, 10.5744}},
{24, {-826.603, -902.404, 11.1009}}, {25, {-672.451, 961.641, 11.2629}},
{26, {-1182.59, -664.16, 11.5362}},  {27, {-53.832, 941.733, 10.5327}},
{28, {-342.819, 1087.5, 20.2285}}, {29, {-53.5578, 943.744, 10.9403}},
{30, {-349.572, 987.994, 47.3406}},  {31, {417.324, 1182.2, 18.665}},
{32, {394.962, -746.423, 10.8907}}, {33, {-379.2, -536.4, 17.2828}},
{34, {-1055.64, -279.919, 11.3088}}, {35, {-1054.39, -278.316, 11.3295}},
{51, {-753.419, 57.5815, 11.0859}}, {52, {-379.2, -536.4, 17.2828}},
{53, {-595.455, 664.144, 10.5583}},   {54, {-611.033, 660.509, 10.9078}},
{55, {-595.699, 655.543, 11.0727}}, {56, {-73.6741, 83.2543, 9.6832}},
{57, {-1160.21, -604.389, 11.6419}}, {58, {-1160.45, -603.709, 11.6419}},
{59, {-1133.01, 38.4004, 18.2163}}, {60, {-962.363, 138.547, 9.24105}},
{61, {-809.363, -162.116, 11.211}}, {62, {-909.884, 90.1468, 15.9513}},
{63, {-868.397, 1165.88, 11.1449}},  {64, {-860.605, 764.613, 10.9149}},
{65, {-885.396, 1054.47, 13.5869}}, {67, {-75.1743, -1035.76, 10.3135}},
{68, {423.19, 51.5079, 11.2382}}, {69, {-9.76481, -1564.36, 10.2926}},
{70, {-676.825, 1196.39, 11.0712}}, {71, {-1368.97, -1258.01, 18.1108}},
{72, {-1431.74, -832.909, 14.0671}}, {73, {-791.172, -12.6376, 11.0899}},
{74, {-1072.16, -1292.58, 11.3494}}};

std::map<int, CVector> gMissionStartCoords = 
{ {2, {208.395, -1287.909, 11.874} }, { 3, {119.088, -826.869, 9.481} },
{ 4, {119.084, -826.870, 9.481} }, { 5, {119.090, -826.862, 9.481} },
{ 6, {119.100, -826.869, 9.481} }, { 7, {-244.2799, -1360.67, 7.132} },
{ 8, {-244.2799, -1360.67, 7.132} }, { 9, {-244.2799, -1360.67, 7.132} },
{ 10, {-244.2799, -1360.67, 7.132} }, { 11, {-244.2799, -1360.67, 7.132} },
{ 12, {-379.2, -536.4, 16.2} }, { 13, {-379.2, -536.4, 16.2} },
{ 14, {-379.2, -536.4, 16.2} }, { 15, {-412.3, -607.0, 16.2} },
{ 16, {-244.6, -491.3, 10.6} }, { 17, {495.74, -82.79, 9.03} },
{ 18, {299.0, -205.0, 10.5} }, { 19, {299.0, -205.0, 10.5} },
{ 20, {299.0, -205.0, 10.5} }, { 21, {493.1, -82.4, 9.8} },
{ 22, {493.1, -82.4, 9.8} }, { 23, {493.1, -82.4, 9.8} },
{ 24, {495.12, -83.39, 9.02} }, { 25, {-1098.8, 342.6, 10.2} },
{ 26, {-1105.0, 334.0, 10.8} }, { 27, {-66.0, 933.04, 10.2} },
{ 28, {-66.0, 933.04, 10.2} }, { 29, {-66.0, 933.04, 10.2} },
{ 30, {-66.0, 933.04, 10.2} }, { 31, {-375.9, -544.6, 16.2} },
{ 32, {-375.9, -544.6, 16.2} }, { 33, {-353.1, -526.4, 11.7} },
{ 34, {-1059.841, -278.7214, 10.4044} }, { 35, {-1059.841, -278.7214, 10.4044} },
{ 51, {-1059.841, -278.7214, 10.4044} }, { 52, {-378.466, -596.1799, 24.7818} },
{ 53, {-597.25, 655.87, 10.06} }, { 54, {-597.25, 655.87, 10.06} },
{ 55, {-597.25, 655.87, 10.06} }, { 56, {-1170.9, -603.7, 10.6} },
{ 57, {-1170.9, -603.7, 10.6} }, { 58, {-1170.9, -603.7, 10.6} },
{ 59, {-1170.9, -603.7, 10.6} }, { 60, {-962.53, 141.69, 8.25} },
{ 61, {-962.53, 141.69, 8.25} }, { 62, {-962.53, 141.69, 8.25} },
{ 63, {-871.9, 1159.46, 10.07} }, { 64, {-871.9, 1159.46, 10.07} },
{ 65, {-871.9, 1159.46, 10.07} }, { 67, {36.8778, -1023.988, 9.4108} },
{ 68, {482.4622, 244.5908, 10.10115} }, { 69, {38.39647, -1023.988, 9.450843} },
{ 70, {-1482.114, -825.2285, 13.8377} }, { 71, {-977.4625, -530.668, 9.9113} },
{ 72, {-1003.098, 207.394, 12.0} }, { 73, {-1003.098, 207.394, 12.0} },
{ 74, {-1003.098, 207.394, 12.0} }};

std::map<int, std::pair<CVector, float>> gMissionTaxiCoords =
{ {3, {{110.6, -824.2, 9.6}, 327.9} },
{ 4, {{110.6, -824.2, 9.6}, 327.9} },
{ 5, {{110.6, -824.2, 9.6}, 327.9} },
{ 6, {{110.6, -824.2, 9.6}, 327.9} },
{ 7, {{-163.0, -1439.4, 9.0}, 201.5} },
{ 8, {{-163.0, -1439.4, 9.0}, 201.5} },
{ 9, {{-163.0, -1439.4, 9.0}, 201.5} },
{ 10, {{-163.0, -1439.4, 9.0}, 201.5} },
{ 11, {{-163.0, -1439.4, 9.0}, 201.5} },
{ 12, {{-288.2, -487.5, 9.8}, 275.0} },
{ 13, {{-288.2, -487.5, 9.8}, 275.0} },
{ 14, {{-288.2, -487.5, 9.8}, 275.0} },
{ 15, {{-288.2, -487.5, 9.8}, 275.0} },
{ 16, {{-288.2, -487.5, 9.8}, 275.0} },
{ 17, {{512.591, -74.9, 9.573}, 189.24} },
{ 18, {{252.7968, -230.9387, 9.8638}, 333.9001} },
{ 19, {{252.7968, -230.9387, 9.8638}, 333.9001} },
{ 20, {{252.7968, -230.9387, 9.8638}, 333.9001} },
{ 21, {{512.591, -74.9, 9.573}, 189.24} },
{ 22, {{512.591, -74.9, 9.573}, 189.24} },
{ 23, {{512.591, -74.9, 9.573}, 189.24} },
{ 24, {{512.591, -74.9, 9.573}, 189.24} },
{ 25, {{-1004.5, 311.1, 9.9}, 155.7} },
{ 26, {{-1004.5, 311.1, 9.9}, 155.7} },
{ 27, {{21.489, 966.28, 9.5}, 172.7} },
{ 28, {{21.489, 966.28, 9.5}, 172.7} },
{ 29, {{21.489, 966.28, 9.5}, 172.7} },
{ 30, {{21.489, 966.28, 9.5}, 172.7} },
{ 31, {{-288.2, -487.5, 9.8}, 275.0} },
{ 32, {{-288.2, -487.5, 9.8}, 275.0} },
{ 33, {{-288.2, -487.5, 9.8}, 275.0} },
{ 34, {{-1045.726, -292.454, 9.758}, 97.607} },
{ 35, {{-1045.726, -292.454, 9.758}, 97.607} },
{ 51, {{-1045.726, -292.454, 9.758}, 97.607} },
{ 52, {{-288.2, -487.5, 9.8}, 275.0} },
{ 53, {{-609.723, 658.861, 9.908}, 279.44} },
{ 54, {{-609.723, 658.861, 9.908}, 279.44} },
{ 55, {{-609.723, 658.861, 9.908}, 279.44} },
{ 56, {{-1173.5, -599.6, 10.2}, 277.1} },
{ 57, {{-1173.5, -599.6, 10.2}, 277.1} },
{ 58, {{-1173.5, -599.6, 10.2}, 277.1} },
{ 59, {{-1173.5, -599.6, 10.2}, 277.1} },
{ 60, {{-957.904, 122.843, 8.278}, 356.948} },
{ 61, {{-957.904, 122.843, 8.278}, 356.948} },
{ 62, {{-957.904, 122.843, 8.278}, 356.948} },
{ 63, {{-860.688, 1169.914, 9.997}, 185.46} },
{ 64, {{-860.688, 1169.914, 9.997}, 185.46} },
{ 65, {{-860.688, 1169.914, 9.997}, 185.46} },
{ 67, {{54.7565, -1031.4596, 10.0117}, 88.0344} },
{ 68, {{454.6711, 233.656, 10.9093}, 271.7515} },
{ 69, {{54.7565, -1031.4596, 10.0117}, 88.0344} },
{ 70, {{-1463.7581, -783.7738, 14.6997}, 180.1} },
{ 71, {{-987.0522, -555.6907, 10.7759}, 179.6947} },
{ 72, {{-1020.8, 191.1, 10.5}, 350.0} },
{ 73, {{-1020.8, 191.1, 10.5}, 350.0} },
{ 74, {{-1020.8, 191.1, 10.5}, 350.0} }};

const int SIZE_MAIN_SCRIPT = 225512;

template<typename T = int>
T &
GetGlobalVariable(uint32_t index) {
	return *reinterpret_cast<T*>(&CTheScripts::ScriptSpace[index * 4]);
}

int Missions::GetRandomMission()
{
	if (Config::mission.forcedMission >= 2 && Config::mission.forcedMission <= 74)
		mRandomizedMission = Config::mission.forcedMission;
	else
		mRandomizedMission = mMissionOrder[mOriginalMission];

	mStoreNextScript = true;
	return mRandomizedMission;
}

void __fastcall Missions::RandomizeMissionToStart(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int& missionId = CTheScripts::ScriptParams[0].iParam;

	if (missionId == 1) // InitAtNewGame
		InitShuffledMissionOrder(nullptr);

	mOriginalMission = missionId;

	if (!gMissionEndOffsets.count(mOriginalMission))
		return;

	missionId = GetRandomMission();

	if (missionId >= START_MISSIONS && missionId <= END_MISSIONS
		&& !IsBlacklistedMission(missionId) && gMissionEndOffsets.count(missionId))
	{
		try
		{
			SetInterior(GetInteriorBasedOnMissionStart(missionId));

			TeleportPlayer(gMissionStartCoords.at(mRandomizedMission), 
				GetIslandFromMissionStart(missionId), missionId);
		}
		catch (...)
		{
		}
		FixStartOfMissions();
	}
}

CRunningScript* Missions::StoreRandomizedScript(uint32_t ip)
{
	CRunningScript* sc = plugin::CallAndReturn<CRunningScript*, 0x450270>(ip);
	if (std::exchange(mStoreNextScript, false)) {
		mRandomizedScript = sc;
		mPostReplaceEndOffsets = gMissionEndOffsets[mOriginalMission];
		mPreReplaceEndOffsets = gMissionEndOffsets[mRandomizedMission];
	}

	return sc;
}

bool Missions::ProcessPreReplaceMissionEndOffsets(CRunningScript* thread, short opcode)
{
	if (mScriptReplaced)
		return false;

	for (int i = 0; i < mPreReplaceEndOffsets.size(); i++)
	{
		auto it = mPreReplaceEndOffsets[i];
		if (thread->m_nIp - SIZE_MAIN_SCRIPT == it.Start)
		{
			thread->m_nIp = it.End + SIZE_MAIN_SCRIPT;

			if (i == mPreReplaceEndOffsets.size() - 1)
				return true;

			continue;
		}
	}

	return false;
}

bool Missions::ProcessPostReplaceMissionEndOffsets(CRunningScript* thread, uint16_t& opcode)
{
	if (!mScriptReplaced)
		return false;

	if (opcode == eScriptCommands::COMMAND_RETURN ||
		thread->m_nIp - SIZE_MAIN_SCRIPT == mPostReplaceEndOffsets.front().End)
	{
		mPostReplaceEndOffsets.erase(mPostReplaceEndOffsets.begin());

		if (!mPostReplaceEndOffsets.size())
		{
			opcode = eScriptCommands::COMMAND_RETURN;
			thread->ProcessOneCommand();

			return true;
		}
		else
			thread->m_nIp = mPostReplaceEndOffsets.front().Start + SIZE_MAIN_SCRIPT;
	}
	return false;
}

void Missions::RestoreOriginalScriptForCleanup()
{
	memcpy((char*)& CTheScripts::ScriptSpace[SIZE_MAIN_SCRIPT],
		mTempMissionData.get(),
		SIZE_MISSION_SCRIPT);

	mScriptReplaced = false;
	mRandomizedScript = nullptr;
}

void Missions::HandleEndThreadOpcode(CRunningScript* thread, short opcode)
{
	if (opcode != eScriptCommands::COMMAND_TERMINATE_THIS_SCRIPT)
		return;

	ResetKaufmanCabs();
	if (mRandomizedMission == 57 && ShouldDestroyFactory)
		DestroyHaitianFactory();
	if (mRandomizedMission == 16 && ShouldOpenMansionDoors)
		OpenMansionDoors();
	if (mRandomizedMission == 51)
		ResetAssets();
	if (mRandomizedMission == 52 && !IsRubOutCompleted() && ShouldCloseMansionDoors)
		CloseMansionDoors(true);

	mRandomizedScript = nullptr;
}

bool Missions::ShouldJump(CRunningScript* thread)
{
	int currentOffset = thread->m_nIp - SIZE_MAIN_SCRIPT;

	uint16_t& opcode = *reinterpret_cast<uint16_t*> (
		&CTheScripts::ScriptSpace[thread->m_nIp]);

	if (ProcessPostReplaceMissionEndOffsets(thread, opcode))
		RestoreOriginalScriptForCleanup();

	HandleEndThreadOpcode(thread, opcode);

	return ProcessPreReplaceMissionEndOffsets(thread, opcode);
}

void Missions::MoveScriptToOriginalOffset(CRunningScript* thread)
{
	int* missionOffsets = (int*)0x7DBED8;

	memcpy(mTempMissionData.get(),
		(char*)& CTheScripts::ScriptSpace[SIZE_MAIN_SCRIPT],
		SIZE_MISSION_SCRIPT);

	int offset = missionOffsets[mOriginalMission];
	CFileMgr::ChangeDir("\\");
	int handle = CFileMgr::OpenFile("data\\main.scm", "rb");
	CFileMgr::Seek(handle, offset, 0);
	CFileMgr::Read(handle, (char*)& CTheScripts::ScriptSpace[SIZE_MAIN_SCRIPT], SIZE_MISSION_SCRIPT);
	CFileMgr::CloseFile(handle);

	if (mRandomizedMission == 57 && ShouldDestroyFactory)
		DestroyHaitianFactory();
	if (mRandomizedMission == 16 && ShouldOpenMansionDoors)
		OpenMansionDoors();
	if (mRandomizedMission == 52 && ShouldCloseMansionDoors)
		CloseMansionDoors(true);
	TeleportPlayerAfterMission();
	ResetKaufmanCabs();
	if (IsFinalAssetMission(mRandomizedMission))
		DoFadeIn();
	if (mRandomizedMission == 51)
		ResetAssets();
	if (mOriginalMission == 52)
		PlayAudioForCredits();

	thread->m_nIp = mPostReplaceEndOffsets.front().Start + SIZE_MAIN_SCRIPT;
	mScriptReplaced = true;
}

void Missions::TeleportPlayerAfterMission()
{
	try
	{
		SetInterior(GetInteriorBasedOnMissionEnd(mOriginalMission));

		TeleportPlayer(gMissionEndCoords.at(mOriginalMission), 
			GetIslandFromMissionEnd(mOriginalMission), -1);
	}
	catch (...) {}
}

char __fastcall Missions::JumpOnMissionEnd(CRunningScript* thread)
{
	if (mRandomizedScript == thread && ShouldJump(thread))
		MoveScriptToOriginalOffset(thread);

	return thread->ProcessOneCommand();
}

void Missions::LoadMissionData(uint8_t* data, uint32_t size)
{
	CPedType::Load(data, size);

	SaveStructure* save
		= reinterpret_cast<SaveStructure*> (
			data + size - sizeof(SaveStructure));

	if (std::string(save->signature, 11) != "RAINBOMIZER")
		return InitShuffledMissionOrder(nullptr);
	return InitShuffledMissionOrder(save);
}

void Missions::InitShuffledMissionOrder(Missions::SaveStructure* structure)
{
	uint32_t seed = RandomNumber(INT_MIN, INT_MAX);
	if (structure)
		seed = structure->randomSeed;

	if (!structure && Config::mission.usingSeed)
		seed = std::hash<std::string>{}(Config::mission.seed);

	std::mt19937 engine{ seed };
	std::uniform_int_distribution<int> d(START_MISSIONS, END_MISSIONS);

	mMissionOrder.Reset();
	for (int i = START_MISSIONS; i <= END_MISSIONS; i++)
		std::swap(mMissionOrder[i], mMissionOrder[d(engine)]);

	for (int i = START_MISSIONS; i <= END_MISSIONS; i++)
	{
		if (IsBlacklistedMission(i) && mMissionOrder[i] != i)
		{
			for (int x = START_MISSIONS; x <= END_MISSIONS; x++)
			{
				if (mMissionOrder[x] == i)
				{
					std::swap(mMissionOrder[x], mMissionOrder[i]);
					break;
				}
			}
		}
	}

	mSaveStructure.randomSeed = seed;
}

void Missions::MissionOrder::Reset()
{
	for (int i = 0; i < TOTAL_MISSIONS; i++)
		Missions[i] = START_MISSIONS + i;
}

void Missions::SaveMissionData(uint8_t* data, uint32_t& outSize)
{
	CPedType::Save(data, &outSize);

	memcpy(data + outSize, &mSaveStructure, sizeof(SaveStructure));
	outSize += sizeof(SaveStructure);
}
bool Missions::IsBlacklistedMission(int missionId)
{
	if (missionId >= 36 && missionId <= 50 || missionId == 66)
		return true;

	return false;
}
eLevelName Missions::GetIslandFromMissionStart(int mission)
{
	if (mission >= 2 && mission <= 24
		|| mission >= 67 && mission <= 69)
		return eLevelName::LEVEL_BEACH;

	if (mission >= 25 && mission <= 35
		|| mission >= 51 && mission <= 65
		|| mission >= 70 && mission <= 74)
		return eLevelName::LEVEL_MAINLAND;

	return eLevelName::LEVEL_GENERIC;
}
eLevelName Missions::GetIslandFromMissionEnd(int mission)
{
	if (mission >= 2 && mission <= 9
		|| mission >= 11 && mission <= 16
		|| mission == 18 || mission == 19
		|| mission == 23 || mission >= 27
		&& mission <= 33 || mission == 52
		|| mission == 56 || mission >= 67
		&& mission <= 69)
		return eLevelName::LEVEL_BEACH;

	if (mission == 10 || mission == 17 ||
		mission == 20 || mission == 21 ||
		mission == 22 || mission >= 24
		&& mission <= 26 || mission == 30
		|| mission == 34 || mission == 35
		|| mission == 51 || mission >= 53
		&& mission <= 55 || mission >= 57
		&& mission <= 65 || mission >= 70
		&& mission <= 74)
		return eLevelName::LEVEL_MAINLAND;

	return eLevelName::LEVEL_GENERIC;
}
void Missions::FixStartOfMissions()
{
	if (mRandomizedMission == 51)
		FixCapTheCollector();

	if (mRandomizedMission >= 72 && mRandomizedMission <= 74)
		FixStartingKaufmanMissions();
}
bool Missions::IsPayphoneMission(int mission)
{
	return mission == 67
		|| mission == 68
		|| mission == 69
		|| mission == 70
		|| mission == 71;
}
bool Missions::IsFinalAssetMission(int mission)
{
	return mission == 16 || mission == 24
		|| mission == 26 || mission == 30
		|| mission == 33 || mission == 35
		|| mission == 52 || mission == 74;
}
Functions::eInterior Missions::GetInteriorBasedOnMissionStart(int mission)
{
	if (mission == 51)
		return eInterior::INTERIOR_MANSION;
	return eInterior::INTERIOR_OUTSIDE;
}
Functions::eInterior Missions::GetInteriorBasedOnMissionEnd(int mission)
{
	switch (mission)
	{
	case 16:
		return eInterior::INTERIOR_MANSION;
	case 22:
		return eInterior::INTERIOR_SHOOTING_RANGE;
	case 31:
		return eInterior::INTERIOR_MALL;
	}
	return eInterior::INTERIOR_OUTSIDE;
}
void Missions::FixCapTheCollector()
{
	int numOfAssets = 0;
	std::vector<int> assets = { 0x821C88, 0x821BFC, 0x821C3C, 
		0x821C64, 0x821C50, 0x821C10 };

	for (int& asset : assets)
		if (injector::ReadMemory<int>(asset) == 1)
			numOfAssets++;

	if (numOfAssets < 2)
	{
		int randomAssetAmount = RandomNumber(2, 5);
		for (int i = numOfAssets; i < randomAssetAmount; i++)
		{
			int rand = RandomNumber(0, assets.size() - 1);
			injector::WriteMemory<int>(assets[rand], 1);
			assets.erase(assets.begin() + rand);
		}
	}
}
void Missions::ResetAssets()
{
	std::vector<int> assets = { 0x821C88, 0x821BFC, 0x821C3C,
	0x821C64, 0x821C50, 0x821C10 };

	for (int& asset : assets)
		injector::WriteMemory<int>(asset, 0);
}
void Missions::ResetKaufmanCabs()
{
	if (injector::ReadMemory<int>(0x82184C) == 1)
		injector::WriteMemory<int>(0x82184C, 0);
}
void Missions::FixStartingKaufmanMissions()
{
	DoFadeIn();

	// Set camera position
	CVector pos1 = { -994.919, 210.472, 15.758 };
	CVector pos2 = { 0.0, 0.0, 0.0 };
	TheCamera.SetCamPositionForFixedMode(pos1, pos2);
	pos2 = { -995.722, 210.02, 15.37 };
	TheCamera.TakeControlNoEntity(pos2, 2, 1);

	UnfreezePlayer();
}
void __fastcall Missions::FixPayphoneMissions(CPed* ped)
{
	ped->ClearAnswerMobile();

	if (ped->IsPlayer() && IsPayphoneMission(mRandomizedMission))
		UnfreezePlayer();
}
void Missions::FixTaxiDestinations(float x, float y, float z, float angle)
{
	if (IsPayphoneMission(mRandomizedMission) && !IsPayphoneMission(mOriginalMission))
		return;

	if (gMissionTaxiCoords.count(mOriginalMission))
	{
		x = gMissionTaxiCoords[mOriginalMission].first.x;
		y = gMissionTaxiCoords[mOriginalMission].first.y;
		z = gMissionTaxiCoords[mOriginalMission].first.z;

		angle = gMissionTaxiCoords[mOriginalMission].second;
	}

	plugin::Call<0x42ADF0>(x, y, z, angle);
}
void __fastcall Missions::SpawnKaufmanForTaxiMissions(CPlayerInfo* player, void* edx, bool safe)
{
	player->MakePlayerSafe(safe);

	if (!safe && IsMission("taxwar1") || IsMission("taxwar2") || IsMission("taxwar3"))
	{
		if (!FindPlayerVehicle())
		{
			int kaufman = 216;
			LoadModel(kaufman);

			if (IsModelLoaded(kaufman))
			{
				plugin::Command<eScriptCommands::COMMAND_CREATE_CAR>(kaufman, -1005.5, 195.7, 11.4);

				for (CVehicle* vehicle : CPools::ms_pVehiclePool)
				{
					int x = vehicle->GetPosition().x;
					int y = vehicle->GetPosition().y;

					if (x == -1005 && y == 195)
					{
						plugin::Command<eScriptCommands::COMMAND_MARK_CAR_AS_NO_LONGER_NEEDED>(vehicle);
						break;
					}
				}
			}
		}
	}
}
void* __fastcall Missions::LoadCortezCutsceneArea(CPools* pool, void* edx, int index)
{
	if (IsMission("lawyer1") || IsMission("generl1") || IsMission("col2")
		|| IsMission("generl3") || IsMission("col_4"))
		LoadArea(FindPlayerPed()->GetPosition(), eLevelName::LEVEL_BEACH);

	return pool->GetObject(index);
}
void __fastcall Missions::KeepYachtAfterAHoD(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int& model = CTheScripts::ScriptParams[0].iParam;

	if (model == GetGlobalVariable(714) || model == GetGlobalVariable(715)
		|| model == GetGlobalVariable(717) || model == GetGlobalVariable(718)
		|| model == GetGlobalVariable(719))
		CTheScripts::ScriptParams[0].iParam = GetGlobalVariable(716);
}
void Missions::RebuildHaitianFactory()
{
	plugin::Command<eScriptCommands::COMMAND_SWAP_NEAREST_BUILDING_MODEL>(
		-1165.346, 85.534, 17.783, 80.0, 1683, 1682);
	plugin::Command<eScriptCommands::COMMAND_SWAP_NEAREST_BUILDING_MODEL>(
		-1165.346, 85.534, 17.783, 80.0, 1704, 1678);
	plugin::Command<eScriptCommands::COMMAND_SWAP_NEAREST_BUILDING_MODEL>(
		-1165.346, 85.534, 17.783, 80.0, 1684, 1651);
}
void Missions::DestroyHaitianFactory()
{
	plugin::Command<eScriptCommands::COMMAND_SWAP_NEAREST_BUILDING_MODEL>(
		-1165.346, 85.534, 17.783, 80.0, 1682, 1683);
	plugin::Command<eScriptCommands::COMMAND_SWAP_NEAREST_BUILDING_MODEL>(
		-1165.346, 85.534, 17.783, 80.0, 1678, 1704);
	plugin::Command<eScriptCommands::COMMAND_SWAP_NEAREST_BUILDING_MODEL>(
		-1165.346, 85.534, 17.783, 80.0, 1651, 1684);

	ShouldDestroyFactory = false;
}
void Missions::OpenMansionDoors()
{
	if (GetGlobalVariable(1789))
	{
		plugin::Command<eScriptCommands::COMMAND_SET_OBJECT_COORDINATES>(GetGlobalVariable(1789),
			-378.542, -554.006, 21.96);
	}
	for (CObject* object : CPools::ms_pObjectPool)
	{
		if (object->m_nModelIndex == 2563)
		{
			plugin::Command<eScriptCommands::COMMAND_DELETE_OBJECT>(object);
			break;
		}
	}
	GetGlobalVariable(1001) = 2;
	ShouldOpenMansionDoors = false;
}
void Missions::CloseMansionDoors(bool isKYFC)
{
	if (GetGlobalVariable(1789))
	{
		plugin::Command<eScriptCommands::COMMAND_SET_OBJECT_COORDINATES>(GetGlobalVariable(1789),
			-378.542, -554.006, -20.0);
		plugin::Command<eScriptCommands::COMMAND_CREATE_OBJECT_NO_OFFSET>(
			2563, -378.542, -554.006, 20.067);
		ShouldOpenMansionDoors = true;
	}
	if (isKYFC && !GetGlobalVariable(1789))
	{
		plugin::Command<eScriptCommands::COMMAND_CREATE_OBJECT_NO_OFFSET>(
			2563, -378.542, -554.006, 20.067);
		ShouldCloseMansionDoors = false;
	}
}
void Missions::RemoveDoorsForKYFC(CEntity* entity)
{
	if (entity->m_nModelIndex == 2563 && IsMission("fin_1"))
	{
		if (!IsRubOutCompleted())
			ShouldCloseMansionDoors = true;
		GetGlobalVariable(1001) = 2;
	}
	CWorld::Remove(entity);
}
bool Missions::IsRubOutCompleted()
{
	return injector::ReadMemory<int>(0x82163C) == 1 ? true : false;
}
int Missions::ReplaceObject(int modelID)
{
	if (modelID == 2446)
		return 2444;
	if (modelID == 2447)
		return 2443;
	if (modelID == 2320)
		return 2319;
	if (modelID == 2321)
		return 2207;
	if (modelID == 2167)
		return 2168;
	if (modelID == 2328)
		return 2327;

	return modelID;
}
bool Missions::ShouldRemoveObject(int modelID)
{
	return modelID == 590 || modelID == 2141 || modelID == 3518
		|| modelID == 3073 || modelID == 1717|| modelID == 857
		|| modelID == 2562;
}
void Missions::SetPositionForStudioGates(CEntity& object)
{
	if (object.m_nModelIndex == 2327)
	{
		object.GetPosition().x = -115.825;
		object.GetPosition().y = 1028.55;
		object.GetPosition().z = 11.334;
	}
	if (object.m_nModelIndex == 2207)
	{
		object.GetPosition().x = -14.381;
		object.GetPosition().y = 884.12;
		object.GetPosition().z = 13.542;
	}
}
bool Missions::ShouldRemoveCarAndPedCube(int x1, int x2)
{
	if (x1 == -230 && x2 == -459)
		return true;
	if (x1 == 189 && x2 == 258)
		return true;
	if (x1 == -102 && x2 == 95)
		return true;
	if (x1 == 161 && x2 == 242)
		return true;
	if (x1 == 136 && x2 == 235)
		return true;
	if (x1 == 49 && x2 == 189)
		return true;
	if (x1 == -258 && x2 == -920)
		return true;
	if (x1 == -787 && x2 == -475)
		return true;
	if (x1 == -129 && x2 == 1097)
		return true;

	return false;
}
void Missions::RemoveBridgesAndObjects(CEntity* entity)
{
	if (ShouldRemoveObject(entity->m_nModelIndex))
		return;

	entity->m_nModelIndex = ReplaceObject(entity->m_nModelIndex);
	SetPositionForStudioGates(*entity);
	CWorld::Add(entity);
}
void Missions::RebuildNonExistingObjects(unsigned char* buffer, unsigned int size)
{
	CPools::LoadObjectPool(buffer, size);
	SetPosAndAngleForStarIslandGate();
}
void __fastcall Missions::SetPosAndAngleForStarIslandGateOnNewGame(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int& model = CTheScripts::ScriptParams[0].iParam;

	if (model == GetGlobalVariable(1780))
		SetPosAndAngleForStarIslandGate();
}
void Missions::SetPosAndAngleForStarIslandGate()
{
	plugin::Command<eScriptCommands::COMMAND_SET_OBJECT_COORDINATES>(GetGlobalVariable(1780), -183.824, -473.223, 12.615);
	plugin::Command<eScriptCommands::COMMAND_SET_OBJECT_HEADING>(GetGlobalVariable(1780), 0.0);
}
void __fastcall Missions::RemoveCarCubes(CPathFind* path, void* edx, float x1, float y1,
	float z1, float x2, float y2, float z2, char a3)
{
	if (!ShouldRemoveCarAndPedCube(x1, x2))
		plugin::CallMethod<0x435AE0>(path, x1, y1, z1, x2, y2, z2, a3);
}
void __fastcall Missions::RemovePedCubes(CPathFind* path, void* edx, float x1, float y1,
	float z1, float x2, float y2, float z2, char a3)
{
	if (!ShouldRemoveCarAndPedCube(x1, x2))
		plugin::CallMethod<0x435980>(path, x1, y1, z1, x2, y2, z2, a3);
}
void __fastcall Missions::ReplaceBuildings(CBuilding* building, void* edx, int modelId)
{
	if (IsMission("cuban2") && building->m_nModelIndex == 1683 && modelId == 1682)
		ShouldDestroyFactory = true;

	building->ReplaceWithNewModel(modelId);
}
void __fastcall Missions::ReplaceFactoryWithFixedModels(CCamera* camera)
{
	camera->RestoreWithJumpCut();
	if (IsMission("cuban2"))
		RebuildHaitianFactory();
}
void Missions::HandleUnloadedAreasAndDoors(CVector* pos)
{
	int x = pos->x;
	int y = pos->y;
	int z = pos->z;

	if (x == 475 && y == -67 && z == 19)
		SetInterior(eInterior::INTERIOR_OUTSIDE);
	if (x == 417 && y == 1182 && z == 18)
		SetInterior(eInterior::INTERIOR_MALL);
	if (x == -282 && y == -511 && z == 11 && mRandomizedMission == 16)
		CloseMansionDoors(false);
	if (x == -378 && y == -596 && z == 24 && mRandomizedMission == 52 && ShouldOpenMansionDoors)
		OpenMansionDoors();
	else if (x == -378 && y == -596 && z == 24 && mRandomizedMission == 52
		&& !IsRubOutCompleted() || mOriginalMission == 16 && mRandomizedMission != 16)
	{
		for (CObject* object : CPools::ms_pObjectPool)
		{
			if (object->m_nModelIndex == 2563)
			{
				plugin::Command<eScriptCommands::COMMAND_DELETE_OBJECT>(object);
				break;
			}
		}
		GetGlobalVariable(1001) = 2;
	}

	CStreaming::LoadScene(pos);
}
void Missions::FixOutsideInterior(eLevelName level)
{
	if (CGame::currArea == eInterior::INTERIOR_OUTSIDE)
		LoadOutsideInterior();

	CStreaming::RemoveBuildingsNotInArea(level);
}
void Missions::Initialise()
{
	if (Config::mission.Enabled)
	{
		plugin::patch::RedirectCall(0x608C27, RandomizeMissionToStart);
		plugin::patch::RedirectCall(0x608CBA, StoreRandomizedScript);
		plugin::patch::RedirectCall(0x44FDB5, JumpOnMissionEnd);
		plugin::patch::RedirectCall(0x61C362, LoadMissionData);
		plugin::patch::RedirectCall(0x61D272, SaveMissionData);

		plugin::patch::RedirectCall(0x62EFD3, FixPayphoneMissions);
		plugin::patch::RedirectCall(0x637F0A, FixTaxiDestinations);
		plugin::patch::RedirectCall(0x4456D8, KeepYachtAfterAHoD);
		plugin::patch::RedirectCall(0x452476, LoadCortezCutsceneArea);
		plugin::patch::RedirectCall(0x4522CE, SpawnKaufmanForTaxiMissions);
		plugin::patch::RedirectCall(0x456422, ReplaceFactoryWithFixedModels);
		plugin::patch::RedirectCall(0x45A0C8, ReplaceBuildings);
		plugin::patch::RedirectCall(0x45AA2C, HandleUnloadedAreasAndDoors);
		plugin::patch::RedirectCall(0x4456F5, RemoveDoorsForKYFC);
		plugin::patch::RedirectCall(0x630B53, FixOutsideInterior);

		plugin::patch::RedirectCall(0x4570DB, RemoveBridgesAndObjects);
		plugin::patch::RedirectCall(0x4BF3EF, RemoveBridgesAndObjects);
		plugin::patch::RedirectCall(0x48AF52, RemoveBridgesAndObjects);
		plugin::patch::RedirectCall(0x48AD9C, RemoveBridgesAndObjects);
		plugin::patch::RedirectCall(0x4570DB, RemoveBridgesAndObjects);
		plugin::patch::RedirectCall(0x452859, SetPosAndAngleForStarIslandGateOnNewGame);
		plugin::patch::RedirectCall(0x61B03C, RebuildNonExistingObjects);
		plugin::patch::RedirectCall(0x45344E, RemoveCarCubes);
		plugin::patch::RedirectCall(0x45852E, RemovePedCubes);

		mTempMissionData = std::make_unique<unsigned char[]>(SIZE_MISSION_SCRIPT);
		mLocalVariables = std::make_unique<unsigned int[]>(16);
	}
}