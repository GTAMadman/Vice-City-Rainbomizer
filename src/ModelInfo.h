#pragma once
#include "CModelInfo.h"
#include <string>
class ModelInfo
{
public:
	static bool IsBlacklistedVehicle(int modelID);
	static bool IsCarModel(int modelID);
	static bool IsRCModel(int modelID);
	static bool IsHeliModel(int modelID);
	static std::string CheckVehicleModel(int modelID);
};