#include "Remote.h"

void Remote::GivePlayerRandomRCVehicle(float x, float y, float z, float angle, short modelId)
{
	// Store the coordinates
	int newX = x;
	int newY = y;
	int newZ = z;

	// Check for vehicle pattern
	int newModel = Script::ProcessScriptVehicleChange(modelId, x, y, z, "null");

	// Change the coordinates
	newX += Script::CheckPatternForMovePosition(modelId, x, y, z).x;
	newY += Script::CheckPatternForMovePosition(modelId, x, y, z).y;
	newZ += Script::CheckPatternForMovePosition(modelId, x, y, z).z;

	LoadModel(newModel);
	if (!IsModelLoaded(newModel))
		newModel = modelId;

	GivePlayerRCVehicle(newX, newY, newZ, angle, newModel);
}
void Remote::GivePlayerRCVehicle(float x, float y, float z, float angle, short modelId)
{
	plugin::CallDynGlobal<float, float, float, float, short>(0x442020, x, y, z, angle, modelId);
}
void Remote::Initialise()
{
	if (Config::rc.Enabled)
	{
		plugin::patch::RedirectCall(0x6075BD, GivePlayerRandomRCVehicle); // RC Raider + RC Baron
		plugin::patch::RedirectCall(0x4458FD, GivePlayerRandomRCVehicle); // RC Bandit

		if (Script::Patterns.size() == 0)
			Script::InitialisePatterns();
	}
}