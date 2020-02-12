#include "Remote.h"

void Remote::GivePlayerRCVehicleHooked(float x, float y, float z, float angle, short modelId)
{
	int newModel = 0;

	// Only initialise if the patterns are empty
	if (scm::Patterns.size() == 0)
		scm::InitialisePatterns();

	// Store the coordinates
	int newX = x;
	int newY = y;
	int newZ = z;

	// Check for vehicle pattern
	newModel = scm::GetIDBasedOnPattern(modelId, x, y, z, "null");

	// Change the coordinates
	newX += scm::CheckPatternForMovePosition(modelId, x, y, z).x;
	newY += scm::CheckPatternForMovePosition(modelId, x, y, z).y;
	newZ += scm::CheckPatternForMovePosition(modelId, x, y, z).z;

	LoadModel(newModel);
	GivePlayerRCVehicle(newX, newY, newZ, angle, newModel);
}
void Remote::GivePlayerRCVehicle(float x, float y, float z, float angle, short modelId)
{
	plugin::CallDynGlobal<float, float, float, float, unsigned short>(0x442020, x, y, z, angle, modelId);
}
void Remote::Initialise()
{
	if (Config::RCVehiclesRandomizer::Enabled)
	{
		plugin::patch::RedirectCall(0x6075BD, GivePlayerRCVehicleHooked); // RC Raider + RC Baron
		plugin::patch::RedirectCall(0x4458FD, GivePlayerRCVehicleHooked); // RC Bandit
	}
}