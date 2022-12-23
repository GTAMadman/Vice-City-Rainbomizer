#pragma once
#include "CModelInfo.h"
#include "Config.h"
class ModelInfo
{
public:
	static bool IsBlacklistedVehicle(int modelID);
	static bool IsCarModel(int modelID);
	static bool IsBoatModel(int modelID);
	static bool IsRCModel(int modelID);
	static bool IsHeliModel(int modelID);
	static bool IsPoliceModel(int modelID);
	static bool IsEmergencyVehicle(int modelID);
	static bool IsMiscVehicle(int modelID);
	static std::string CheckVehicleModel(int modelID);
};