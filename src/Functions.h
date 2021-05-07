#pragma once
#include "plugin.h"
#include "CStreaming.h"
#include "CModelInfo.h"
#include "ModelInfo.h"
#include "CRunningScript.h"
#include "eLevelName.h"
#include "CGame.h"
#include "CCamera.h"
#include "CWorld.h"
#include "CRubbish.h"
#include "CTimeCycle.h"
#include <ctime>
#include <random>

class Functions
{
private:
	static std::mt19937 rngEngine;
	static int* ms_numVehiclesLoaded;
public:
	static int RandomNumber(int min, int max);
	static void LoadModel(int modelID);
	static char* GetThreadName();
	static std::string GetRainbomizerDir();
	static bool DoCoordinatesMatch(int x1, int y1, int z1, int x2, int y2, int z2);
	static bool IsModelLoaded(int modelID);
	static bool ClumpExist(int modelID);
	static int GetNumberOfVehiclesLoaded();
	static int GetRandomLoadedVehicle();
	static bool IsRampageRunning();
	static void PlayAudioForCredits();
	static bool GetWaterLevel(float fX, float fY, float fZ, float* pfOutLevel, bool bDontCheckZ);

	enum eInterior
	{
		INTERIOR_OUTSIDE = 0,
		INTERIOR_HOTEL,
		INTERIOR_MANSION,
		INTERIOR_BANK,
		INTERIOR_MALL,
		INTERIOR_STRIPCLUB,
		INTERIOR_LAWYERS,
		INTERIOR_CAFE_ROBINA,
		INTERIOR_CONCERT,
		INTERIOR_STUDIO,
		INTERIOR_SHOOTING_RANGE,
		INTERIOR_APARTMENT_AND_BIKER_BAR,
		INTERIOR_POLICEHQ,
		INTERIOR_STADIUM1 = 14,
		INTERIOR_STADIUM2,
		INTERIOR_STADIUM3,
		INTERIOR_MALIBU_CLUB,
		INTERIOR_PRINT_WORKS
	};

	template <typename T> static auto& GetRandomElement(T& container)
	{
		auto it = std::begin(container);
		std::advance(it, RandomNumber(0, std::size(container) - 1));

		return *it;
	}
	template <typename T, typename V>
	static bool DoesElementExist(const T& container, const V val)
	{
		return std::find(std::begin(container), std::end(container),
			val)
			!= std::end(container);
	}

	static void SortOutCollisionAfterLoad();
	static void RequestCollision(CVector& pos);
	static void DoFadeIn();
	static void UnfreezePlayer();
	static bool DoesMissionPutPlayerInVehicleOnStart(int mission);
	static void SetInterior(eInterior interior);
	static void LoadArea(CVector& pos, eLevelName level);
	static void LoadOutsideInterior();
	static void TeleportPlayer(CVector& pos, eLevelName level, int newMission);
};

class cMusicManager
{
public:
	void ChangeMusicMode(int mode);
	void PlayFrontEndTrack(int sound, char arg1);
};
extern cMusicManager& gMusicManager;