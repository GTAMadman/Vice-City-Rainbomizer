#include "Functions.h"

int* Functions::ms_numVehiclesLoaded = reinterpret_cast<int*>(0xA10858);
CRunningScript*& pActiveScripts = *(CRunningScript * *)0x975338;
cMusicManager& gMusicManager = *(cMusicManager*)0x980038;

/* Initialised the random engine and given it a seed */
std::mt19937 Functions::rngEngine{ (unsigned int)time(0) };

void Functions::LoadModel(int modelID)
{
	if (CStreaming::ms_aInfoForModel[modelID].m_nLoadState != 1)
	{
		CStreaming::RequestModel(modelID, 0);
		CStreaming::LoadAllRequestedModels(false);
	}
}
int Functions::RandomNumber(int min, int max)
{
	std::uniform_int_distribution random(min, max);
	return random(rngEngine);
}
char* Functions::GetThreadName()
{
	return pActiveScripts->m_szName;
}
std::string Functions::GetRainbomizerDir()
{
	return std::string(plugin::paths::GetGameDirPathA()) + "rainbomizer/";
}
bool Functions::DoCoordinatesMatch(int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (x1 == x2 && y1 == y2 && z1 == z2)
		return true;
	return false;
}
bool Functions::IsRampageRunning()
{
	if (injector::ReadMemory<short>(0xA10A72) == 1)
		return true;

	return false;
}
bool Functions::IsModelLoaded(int modelID)
{
	if (CStreaming::ms_aInfoForModel[modelID].m_nLoadState == 1)
	{
		if (modelID >= 0 && modelID <= 106 || modelID >= 130 && modelID <= 236)
			if (!ClumpExist(modelID))
				return false;

		return true;
	}
	return false;
}
bool Functions::ClumpExist(int modelID)
{
	if (static_cast<CClumpModelInfo*>(CModelInfo::ms_modelInfoPtrs[modelID])->m_pClump)
		return true;
	return false;
}
int Functions::GetNumberOfVehiclesLoaded()
{
	return *ms_numVehiclesLoaded;
}
int Functions::GetRandomLoadedVehicle()
{
	return CStreaming::ms_vehiclesLoaded[RandomNumber(0, GetNumberOfVehiclesLoaded() - 1)];
}
bool Functions::GetWaterLevel(float fX, float fY, float fZ, float* pfOutLevel, bool bDontCheckZ)
{
	return plugin::CallAndReturn<bool, 0x5C2C80>(fX, fY, fZ, pfOutLevel, bDontCheckZ);
}
void Functions::SortOutCollisionAfterLoad()
{
	plugin::Call<0x4167F0>();
}
void Functions::RequestCollision(CVector& pos)
{
	plugin::Call<0x62A140>(&pos);
}
void Functions::DoFadeIn()
{
	plugin::CallMethod<0x46FBCB>(&TheCamera, 1500, 1);
}
void Functions::UnfreezePlayer()
{
	injector::WriteMemory<bool>(0xA10B51, true);
	plugin::Call<0x4069D0>();
	CPad::GetPad(CWorld::PlayerInFocus)->Clear(true);
}
void Functions::PlayAudioForCredits()
{
	int radio = 0;
	while ((radio = RandomNumber(0, 8), radio == 2 || radio == 5)); // Excluded talk radio

	gMusicManager.ChangeMusicMode(0);
	gMusicManager.PlayFrontEndTrack(radio, 1);
}
void cMusicManager::ChangeMusicMode(int mode)
{
	plugin::CallMethod<0x5FC540>(this, mode);
}
void cMusicManager::PlayFrontEndTrack(int sound, char arg1)
{
	plugin::CallMethod<0x5FA5B0>(this, sound, arg1);
}
bool Functions::DoesMissionPutPlayerInVehicleOnStart(int mission)
{
	return mission == 23 || mission == 56 
		|| mission == 13 || mission == 65 
		|| mission == 26 || mission == 11;
}
void Functions::SetInterior(eInterior interior)
{
	CGame::currArea = interior;
	CStreaming::RemoveBuildingsNotInArea(interior);

	if (interior == eInterior::INTERIOR_OUTSIDE)
		LoadOutsideInterior();
}
void Functions::LoadOutsideInterior()
{
	injector::WriteMemory<float>(0x686FC8, 1.0);
	CRubbish::SetVisibility(true);
	CTimeCycle::StopExtraColour(false);
}
void Functions::LoadArea(CVector& pos, eLevelName level)
{
	CStreaming::ms_disableStreaming = 0;
	CGame::currLevel = level;

	CStreaming::RemoveBuildingsNotInArea(level);
	SortOutCollisionAfterLoad();
	RequestCollision(pos);
	CStreaming::StreamZoneModels(&pos);
	CStreaming::LoadScene(&pos);
	CStreaming::RequestBigBuildings(level);
	CStreaming::LoadSceneCollision(&pos);

	CStreaming::LoadAllRequestedModels(false);
}
void Functions::TeleportPlayer(CVector& pos, eLevelName level, int newMission)
{
	LoadArea(pos, level);

	// Kaufman Cab missions + AHoD
	if (FindPlayerVehicle() && DoesMissionPutPlayerInVehicleOnStart(newMission))
	{
		CVehicle* vehicle = FindPlayerVehicle();
		FindPlayerPed()->RemoveInCarAnims(true);
		vehicle->m_pDriver = nullptr;
		FindPlayerPed()->m_bInVehicle = false;
		FindPlayerPed()->RestartNonPartialAnims();
		FindPlayerPed()->SetInitialState();
		vehicle->m_nVehicleFlags.bHasDriver = false;
	}

	FindPlayerEntity()->Teleport(pos);

	if (FindPlayerPed() && !FindPlayerVehicle())
		FindPlayerPed()->SetInitialState();
}