#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "Traffic.h"
#include "ModelInfo.h"
#include "CCarGenerator.h"

class Parked : Functions
{
public:
	static void Initialise();
	static void __fastcall ParkedVehiclesRandomizer(CCarGenerator* gen);
	static void* __fastcall CarparkVehiclesRandomizer(CVehicle* vehicle, void* edx, int model, char createdBy);
};