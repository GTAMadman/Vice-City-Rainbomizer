#pragma once
#include "plugin.h"
#include "scm.h"
#include "Config.h"
#include "Functions.h"

class Remote : Functions
{
public:
	static void Initialise();
private:
	static void GivePlayerRCVehicleHooked(float x, float y, float z, float angle, short modelId);
	static void GivePlayerRCVehicle(float x, float y, float z, float angle, short modelID);
};

