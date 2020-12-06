#pragma once
#include "plugin.h"
#include "Script.h"
#include "Config.h"
#include "Functions.h"

class Remote : Functions
{
public:
	static void Initialise();
private:
	static void GivePlayerRandomRCVehicle(float x, float y, float z, float angle, short modelId);
	static void GivePlayerRCVehicle(float x, float y, float z, float angle, short modelID);
};