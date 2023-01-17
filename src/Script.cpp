#include "Script.h"

std::vector<Script::Pattern> Script::Patterns;
std::vector<int> Script::AlloyWheelsVehicles;
void __fastcall Script::ScriptVehicleRandomizer(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);

	int origModel = CTheScripts::ScriptParams[0].iParam;
	int newModel = 0;

	// Stored coordinates
	int x = CTheScripts::ScriptParams[1].fParam;
	int y = CTheScripts::ScriptParams[2].fParam;
	int z = CTheScripts::ScriptParams[3].fParam;
	int newX = x;
	int newY = y;
	int newZ = z;

	/* RC Vehicles can spawn through this function */
	if (!Config::rc.Enabled && IsRCModel(origModel))
		newModel = origModel;

	if (newModel != origModel)
		newModel = ProcessScriptVehicleChange(origModel, x, y, z, script->m_szName);

	// Attempt to load the vehicle
	LoadModel(newModel);

	// If the vehicle isn't loaded, return the original
	if (!IsModelLoaded(newModel))
		newModel = origModel;

	CTheScripts::ScriptParams[0].iParam = newModel;

	// Change the coordinates
	CVector posn = CheckPatternForMovePosition(origModel, x, y, z);
	newX += posn.x;
	newY += posn.y;
	newZ += posn.z;

	if (!DoCoordinatesMatch(newX, newY, newZ, x, y, z))
	{
		// Set the new position
		CTheScripts::ScriptParams[1].fParam = newX;
		CTheScripts::ScriptParams[2].fParam = newY;
		CTheScripts::ScriptParams[3].fParam = newZ;
	}

	// Added Alloy Wheels Fix here
	AlloyWheelsFix(newModel);
}
void Script::FixForcedPlayerVehicleType(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int& modelId = CTheScripts::ScriptParams[1].iParam;

	// Alloy Wheels of Steal
	if (IsMission("bike1") && modelId == 193 || modelId == 166)
	{
		if (FindPlayerVehicle())
			modelId = FindPlayerVehicle()->m_nModelIndex;
	}
	// Dirtring
	if (IsMission("kickst") && modelId == 198)
	{
		if (FindPlayerVehicle())
			modelId = FindPlayerVehicle()->m_nModelIndex;
	}
	// Kaufman Cab Missions & Checkpoint Charie
	if (modelId == 216 || modelId == 176)
	{
		if (FindPlayerVehicle())
			modelId = FindPlayerVehicle()->m_nModelIndex;
	}
	// Cherry Poppers
	if (modelId == 153)
	{
		if (FindPlayerVehicle())
		{
			if (FindPlayerVehicle()->UsesSiren() || FindPlayerVehicle()->m_nModelIndex == 153)
				modelId = FindPlayerVehicle()->m_nModelIndex;
		}
	}

	if (Config::script.offroadEnabled)
	{
		if (modelId == 169 || modelId == 191)
			if (FindPlayerVehicle())
				modelId = FindPlayerVehicle()->m_nModelIndex;

		/* Separated these and only allowed cars/bikes due to an issue with the checkpoints */

		// Test Track
		if (modelId == 130)
			if (FindPlayerVehicle())
				if (ModelInfo::IsCarModel(FindPlayerVehicle()->m_nModelIndex)
					|| ModelInfo::IsHeliModel(FindPlayerVehicle()->m_nModelIndex))
					modelId = FindPlayerVehicle()->m_nModelIndex;

		// Trial By Dirt
		if (modelId == 198)
			if (FindPlayerVehicle())
				if (CModelInfo::IsBikeModel(FindPlayerVehicle()->m_nModelIndex))
					modelId = FindPlayerVehicle()->m_nModelIndex;
	}
	if (Config::script.rcEnabled)
	{
		if (modelId == 189)
			if (FindPlayerVehicle())
				modelId = FindPlayerVehicle()->m_nModelIndex;
	}
	if (Config::script.chopperCheckpointEnabled)
	{
		if (modelId == 199)
		{
			if (FindPlayerVehicle())
				if (ModelInfo::IsHeliModel(FindPlayerVehicle()->m_nModelIndex))
					modelId = FindPlayerVehicle()->m_nModelIndex;
		}
	}
	if (Config::script.pizzaBoyEnabled)
	{
		if (modelId == 178)
			if (FindPlayerVehicle())
				modelId = FindPlayerVehicle()->m_nModelIndex;
	}
}
void Script::FixForcedPedVehicleType(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int& modelId = CTheScripts::ScriptParams[1].iParam;

	if (IsMission("bike1") && modelId == 166)
		modelId = AlloyWheelsVehicles[RandomNumber(0, AlloyWheelsVehicles.size() - 1)];
}
void __fastcall Script::FixTrojanVoodooForcedVehicle(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int& modelId = CTheScripts::ScriptParams[1].iParam;

	if (IsMission("cuban4") && modelId == 142)
	{
		if (FindPlayerVehicle())
			modelId = FindPlayerVehicle()->m_nModelIndex;
	}
}
void* __fastcall Script::CreateRandomizedCab(CVehicle* vehicle, void* edx, int modelId, bool createdBy)
{
	int newModel;

	while ((newModel = RandomNumber(130, 236)), ModelInfo::IsMiscVehicle(newModel) || 
		ModelInfo::IsBlacklistedVehicle(newModel) || ModelInfo::IsRCModel(newModel) || CModelInfo::IsBoatModel(newModel) || 
		newModel == 155 || newModel == 178 || newModel == 215 || newModel < 130 || newModel > 236); // Hunter, Pizza Boy, Baggage

	LoadModel(newModel);

	if (!IsModelLoaded(newModel))
		newModel = modelId;

	if (CModelInfo::IsHeliModel(newModel))
		reinterpret_cast<CHeli*>(vehicle)->CHeli::CHeli(newModel, createdBy);

	if (CModelInfo::IsBikeModel(newModel))
		reinterpret_cast<CBike*>(vehicle)->CBike::CBike(newModel, createdBy);

	if (CModelInfo::IsCarModel(newModel))
		reinterpret_cast<CAutomobile*>(vehicle)->CAutomobile::CAutomobile(newModel, createdBy);

	return vehicle;
}
void __fastcall Script::FixBombsAwayVan(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);

	/* As it resets the vehicle position, I have to change it here instead */
	if (IsMission("hait2"))
	{
		int x = CTheScripts::ScriptParams[1].fParam;
		int y = CTheScripts::ScriptParams[2].fParam;
		int z = CTheScripts::ScriptParams[3].fParam;

		if (x == -808 && y == -162 && z == 10)
			CTheScripts::ScriptParams[2].fParam += 15;
	}
}
void Script::FixBombsAwayBombPosition(CPhysical* phy1, CPhysical* phy2, CVector offset)
{
	if (IsMission("hait2") && phy2->m_nModelIndex == 564 && !IsRCModel(phy1->m_nModelIndex))
	{
		if (phy1->m_nModelIndex == 155)
			offset.z -= 1.5f;
		else
			offset.z -= 0.5f;
	}

	CPhysical::PlacePhysicalRelativeToOtherPhysical(phy1, phy2, offset);
}
void __fastcall Script::FixFrozenLoadingScreens(CRunningScript* script, void* edx, char flag)
{
	injector::WriteMemory<char>(0xA10B63, 0);
	script->UpdateCompareFlag(flag);
}
bool Script::FixWaterLevelCrash(float fX, float fY, float fZ, float* pfOutLevel, bool bDontCheckZ)
{
	int x = (((fX + (400.0f)) + (((2048.0f - -2048.0f)) / 2)) / 32);
	int y = (((fY)+(((2048.0f - -2048.0f)) / 2)) / 32);

	if (x < 0 || x >= 128) return false;
	if (y < 0 || y >= 128) return false;

	return GetWaterLevel(fX, fY, fZ, pfOutLevel, bDontCheckZ);
}
void* __fastcall Script::OpenBootFix(CAutomobile* vehicle)
{
	if (!vehicle->m_aCarNodes[18])
		return vehicle;

	vehicle->PopBoot();
	return vehicle;
}
void Script::AlloyWheelsFix(int modelID)
{
	/* Checking for "Alloy Wheels of Steel" - this will store the bikes
	that the bikers are driving so they can go through checkpoints */
	if (IsMission("bike1"))
		AlloyWheelsVehicles.push_back(modelID);
	else
		if (AlloyWheelsVehicles.size() > 0)
			AlloyWheelsVehicles.clear();
}
void Script::InitialisePatterns()
{
	/* General Patterns */
	Pattern pattern = { .gVehicle = {"car"}, .allowedType = {"car", "bike"} };
	Patterns.push_back(pattern);

	pattern = { .gVehicle = {"bike"}, .allowedType = {"car", "bike"} };
	Patterns.push_back(pattern);

	pattern = { .gVehicle = {"boat"}, .allowedType = {"boat"} };
	Patterns.push_back(pattern);

	pattern = { .gVehicle = {"heli"}, .allowedType = {"heli"} };
	Patterns.push_back(pattern);


	/* Script Vehicle Patterns */

	// Coach
	pattern = { .vehicle = {167}, .allowed = {167, 161} };
	Patterns.push_back(pattern);

	// Skimmer
	pattern = { .vehicle = {190}, .allowed = {190}, .allowedType = {"heli"}, .move = {65, -14, 3}, .moveType = {"heli"} };
	Patterns.push_back(pattern);

	// Avery's Stretch
	pattern = { .vehicle = {139}, .denied = {167}, .allowedType = {"car", "bike"}, .coords = {306, -241, 12} };
	Patterns.push_back(pattern); // Crashes as a Coach for some reason

	// RC Bandit
	pattern = { .vehicle = {171}, .allowedType = {"car", "rc"} };
	Patterns.push_back(pattern);

	// RC Baron
	pattern = { .vehicle = {194}, .allowed = {194, 195, 231}, .allowedType = {"heli"} };
	Patterns.push_back(pattern);

	// RC Raider
	pattern = { .vehicle = {195}, .allowed = {195, 231, 194} };
	Patterns.push_back(pattern);

	// RC Goblin
	pattern = { .vehicle = {231}, .allowed = {231, 195, 194} };
	Patterns.push_back(pattern);

	// Sanchez - Dirtring
	pattern = { .vehicle = {198}, .allowedType = {"bike"}, .coords = {-1331, 1454, 298} };
	Patterns.push_back(pattern);

	// Taxi - The Job
	pattern = { .vehicle = {150}, .allowed = {167}, .denied = {217, 227, 228, 189}, .coords = {496, -84, 9}, .door_check = {true} };
	Patterns.push_back(pattern);

	// Speeder - Stunt Boat Challenge
	pattern = { .vehicle = {182}, .allowed = {182, 223, 160, 176}, .coords = {-90, 105, 5} };
	Patterns.push_back(pattern);

	// Vigilante
	pattern = { .thread = {"copcar"}, .door_check = {true} };
	Patterns.push_back(pattern);

	// Firefighter
	pattern = { .thread = {"firetru"} };
	Patterns.push_back(pattern); // Using thread only will return the original vehicle

	// Publicity Tour
	pattern = { .vehicle = {201}, .allowed = {217, 227}, .denied = {167, 161, 218, 155, 177, 199, 189}, 
	.allowedType = {"heli"}, .coords = {-872, 1151, 11}, .move = {3, 0, 0}, .door_check = {true}, .moveType = {"heli"} };
	Patterns.push_back(pattern);

	// The Chase - BF Injection
	pattern = { .vehicle = {154}, .denied = {178, 215}, .allowedType = {"car", "bike"}, .thread = {"baron1"} };
	Patterns.push_back(pattern);

	// Phnom Penh '86 - Maverick
	pattern = { .vehicle = {217}, .allowedType = {"car", "heli", "rc"}, .thread = {"baron2"} };
	Patterns.push_back(pattern);

	// Phnom Pehn '86 - Sparrow
	pattern = { .vehicle = {199}, .allowedType = {"car", "heli", "rc"}, .thread = {"baron2"} };
	Patterns.push_back(pattern);

	// Phnom Pehn '86 - Sea Sparrow
	pattern = { .vehicle = {177}, .allowedType = {"car", "heli", "rc"}, .thread = {"baron2"} };
	Patterns.push_back(pattern);

	// Hog Tied
	pattern = { .vehicle = {166}, .allowed = {130, 131, 132, 134, 135, 140, 141, 142, 143, 
		145, 147, 148, 149, 150, 151, 152, 153, 154, 156, 159, 164, 168, 169, 170, 172, 
		174, 175, 179, 187, 188, 189, 196, 197, 200, 204, 205, 206, 207, 208, 209, 210, 211,
		212, 215, 216, 219, 220, 221, 222, 224, 225, 226, 230, 232, 233, 234, 235, 236}, 
		.allowedType = {"bike", "heli"}, .coords = {-700, 1300, 10}, .move = {-16, -15, 1}, .moveType = {"heli"} };
	Patterns.push_back(pattern); // Allowed small cars, bikes and heli's

	// Bar Brawl - Bike 1
	pattern = { .vehicle = {191}, .coords = {357, -745, 10}, .move = {3, 0, 0} };
	Patterns.push_back(pattern);

	// Bar Brawl - Bike 2
	pattern = { .vehicle = {191}, .coords = {359, -742, 10}, .move = {-5, -15, 0} };
	Patterns.push_back(pattern);

	// Bombs Away
	pattern = { .vehicle = {194}, .allowed = {194, 195, 231}, .allowedType = {"heli"}, .coords = {-812, -168, 10},
	.move = {0, -10, 0}, .moveType = {"heli"} };
	Patterns.push_back(pattern);

	// Back Alley Brawl
	pattern = { .vehicle = {141}, .denied = {178, 215}, .allowedType {"car", "bike"}, .thread = {"lawyer2"} };
	Patterns.push_back(pattern);

	// Guardian Angels - Infernus
	pattern = { .vehicle = {141}, .coords = {132, -1211, 15}, .move = {0, 0, 3} };
	Patterns.push_back(pattern);

	// Guardian Angels - Diaz's Admiral on arrival to the deal
	pattern = { .vehicle = {175}, .allowed = {167, 161}, .coords = {463, -461, 9}, .door_check = {true} };
	Patterns.push_back(pattern);

	// Supply & Demand - Squalo
	pattern = { .vehicle = {176}, .allowed = {182, 202, 223, 160, 176}, .coords = {-378, -660, 5} };
	Patterns.push_back(pattern);

	// The Fastest Boat - Squalo
	pattern = { .vehicle = {176}, .allowed = {182, 202, 223, 160, 176, 190}, .thread = {"baron3"} };
	Patterns.push_back(pattern);

	// All Hands on Deck - Maverick
	pattern = { .vehicle = {217}, .allowedType = {"car", "heli"}, .thread = {"col_5"} };
	Patterns.push_back(pattern);

	// All Hands on Deck - Hunter
	pattern = { .vehicle = {155}, .allowedType = {"car", "heli", "rc"}, .thread = {"col_5"} };
	Patterns.push_back(pattern);

	// Hit the Courier - Maverick
	pattern = { .vehicle = {217}, .allowedType = {"car", "heli", "rc"}, .thread = {"count2"} };
	Patterns.push_back(pattern);

	// Cop Land - police car
	pattern = { .vehicle = {156}, .coords = {469, 336, 11}, .move = {0, -5, 0} };
	Patterns.push_back(pattern);

	// Cannon Fodder - Pony
	pattern = { .vehicle = {143}, .coords = {-1161, 76, 10}, .move = {-3, 0, 0} };
	Patterns.push_back(pattern);

	// Naval Engagement - Jetmax
	pattern = { .vehicle = {223}, .denied = {190, 184, 136}, .allowedType = {"boat"}, .coords = {-722, -1163, 5} };
	Patterns.push_back(pattern);

	// V.I.P - Taxi
	pattern = { .vehicle = {150}, .denied = {178, 215}, .allowedType = {"car", "bike"}, .coords = {-546, -474, 10} };
	Patterns.push_back(pattern);

	// Martha's Mug Shot - Sparrow
	pattern = { .vehicle = {199}, .allowedType = {"car", "bike", "heli"}, .coords = {-61, 1019, 9} };
	Patterns.push_back(pattern);

	// Martha's Mug Shot - Stretch
	pattern = { .vehicle = {139}, .denied = {178, 215}, .allowedType = {"car", "bike"}, .thread = {"porno3"} };
	Patterns.push_back(pattern);

	// G-Spotlight - PCJ
	pattern = { .vehicle = {191}, .allowedType = {"bike"}, .thread = {"porno4"} };
	Patterns.push_back(pattern);

	// Psycho Killer
	pattern = { .vehicle = {201}, .allowedType = {"car", "bike", "heli"}, .thread = {"rockb2"} };
	Patterns.push_back(pattern);

	// Gun Runner
	pattern = { .vehicle = {200}, .allowedType = {"car", "bike", "heli"}, .thread = {"phil1"} };
	Patterns.push_back(pattern);

	// Boomshine Saigon
	pattern = { .vehicle = {200}, .allowedType = {"car", "bike", "heli"}, .move = {4, 0, 0},
	.thread = {"phil2"}, .moveType = {"heli"} };
	Patterns.push_back(pattern);

	// Check Out at the Check In - Maverick
	pattern = { .vehicle = {217}, .allowedType = {"heli", "car", "bike"}, .thread = {"assin4"} };
	Patterns.push_back(pattern);

	// Loose Ends - Maverick
	pattern = { .vehicle = {217}, .allowedType = {"heli", "car", "bike"}, .thread = {"assin5"} };
	Patterns.push_back(pattern);
}
/* I've only built the pattern system to work with the necessary patterns for the main game.
   Currently this isn't a great way to do it, but this may be changed in future. */
int Script::ProcessScriptVehicleChange(int origModel, int x, int y, int z, std::string thread)
{
	if (Config::script.forcedVehicle >= 130 && Config::script.forcedVehicle <= 236)
		return Config::script.forcedVehicle;

	// Scripted Vehicle Patterns
	for (int i = 0; i < Patterns.size(); i++)
	{
		int index = i;
		if (Patterns[index].vehicle == origModel)
		{
			// Check for more than one vehicle in pattern (checking using coordinates)
			// This will allow multiple vehicles to be used in the patterns - as long as they have coords!
			for (int a = 0; a < Patterns.size(); a++)
			{
				if (DoCoordinatesMatch(Patterns[a].coords[0], Patterns[a].coords[1], Patterns[a].coords[2], x, y, z))
				{
					index = a;
					break;
				}
			}
			std::vector<int> vehicles;

			if (DoCoordinatesMatch(Patterns[index].coords[0], Patterns[index].coords[1], Patterns[index].coords[2], 0, 0, 0))
				vehicles = Patterns[index].allowed;

			std::vector<int> deniedVehicles = Patterns[index].denied;

			// Coordinate check only
			if (DoCoordinatesMatch(Patterns[index].coords[0], Patterns[index].coords[1], Patterns[index].coords[2], x, y, z))
			{
				vehicles = Patterns[index].allowed;
				std::vector<int> newVehicles = ProcessVehicleTypes(Patterns[index]);
				for (int a = 0; a < newVehicles.size(); a++)
					vehicles.push_back(newVehicles[a]);
			}
			// Thread check only
			if (Patterns[index].thread == thread)
			{
				vehicles = Patterns[index].allowed;
				std::vector<int> newVehicles = ProcessVehicleTypes(Patterns[index]);
				for (int a = 0; a < newVehicles.size(); a++)
					vehicles.push_back(newVehicles[a]);
			}
			// Coordinate and door check
			if (DoCoordinatesMatch(Patterns[index].coords[0], Patterns[index].coords[1], Patterns[index].coords[2], x, y, z) &&
				Patterns[index].door_check)
			{
				vehicles = Patterns[index].allowed;
				for (int model = 130; model < 237; model++)
				{
					if (CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(model) > 2)
						vehicles.push_back(model);
				}
			}
			// Any other check that uses allowed types
			if (Patterns[index].allowedType.size() > 0)
			{
				// If this pattern has coordinates or a thread check, don't run this
				if (DoCoordinatesMatch(Patterns[index].coords[0], Patterns[index].coords[1], Patterns[index].coords[2], 0, 0, 0)
					&& Patterns[index].thread == "")
				{
					vehicles = Patterns[index].allowed;
					std::vector<int> newVehicles = ProcessVehicleTypes(Patterns[index]);
					for (int a = 0; a < newVehicles.size(); a++)
						vehicles.push_back(newVehicles[a]);
				}
			}
			// Remove any denied vehicles
			if (Patterns[index].denied.size() > 0)
			{
				for (int x = 0; x < Patterns[index].denied.size(); x++)
				{
					vehicles.erase(std::remove(vehicles.begin(), vehicles.end(),
						Patterns[index].denied[x]), vehicles.end());
				}
			}
			if (vehicles.size() > 0)
			{
				Patterns[index].chosen = vehicles[RandomNumber(0, vehicles.size() - 1)];
				return Patterns[index].chosen;
			}
		}

		/* Patterns without a vehicle check */

		std::vector<int> vehicles = Patterns[index].allowed;

		// Thread and door check - used for Vigilante and Firefighter
		if (Patterns[index].thread == thread)
		{
			if (Patterns[index].door_check)
			{
				for (int model = 130; model < 237; model++)
				{
					if (CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(model) > 2)
						vehicles.push_back(model);
				}
				if (vehicles.size() > 0)
				{
					Patterns[index].chosen = vehicles[RandomNumber(0, vehicles.size() - 1)];
					return Patterns[index].chosen;
				}
			}
			if (Patterns[index].vehicle == 0)
				return origModel;
		}
	}

	/* General Vehicle Patterns */

	// Added this as a safety precaution
	if (CheckVehicleModel(origModel) == "unknown")
		return origModel;

	std::vector<int> vehicles;
	for (int i = 0; i < Patterns.size(); i++)
	{
		if (Patterns[i].gVehicle == CheckVehicleModel(origModel))
		{
			vehicles = ProcessVehicleTypes(Patterns[i]);
			break;
		}
	}
	if (vehicles.size() > 0)
		return vehicles[RandomNumber(0, vehicles.size() - 1)];
	return origModel; // Return original
}
CVector Script::CheckPatternForMovePosition(int origModel, int x, int y, int z)
{
	CVector position;
	position.x = 0, position.y = 0, position.z = 0;
	int index = 0;

	// Get the pattern by coordinates (checks for multiple patterns with the same vehicle)
	for (int i = 0; i < Patterns.size(); i++)
	{
		if (DoCoordinatesMatch(Patterns[i].coords[0], Patterns[i].coords[1], Patterns[i].coords[2], x, y, z))
		{
			index = i;
			break;
		}
	}

	// Check the vehicle
	if (Patterns[index].vehicle == origModel)
	{
		if (Patterns[index].allowedType.size() > 0)
		{
			for (int x = 0; x < Patterns[index].moveType->size(); x++)
			{
				if (IsCarModel(Patterns[index].chosen) && Patterns[index].moveType[x] == "car")
				{
					position.x = Patterns[index].move[0];
					position.y = Patterns[index].move[1];
					position.z = Patterns[index].move[2];
					return position;
				}
				if (IsHeliModel(Patterns[index].chosen) && Patterns[index].moveType[x] == "heli")
				{
					position.x = Patterns[index].move[0];
					position.y = Patterns[index].move[1];
					position.z = Patterns[index].move[2];
					return position;
				}
				if (CModelInfo::IsBikeModel(Patterns[index].chosen) && Patterns[index].moveType[x] == "bike")
				{
					position.x = Patterns[index].move[0];
					position.y = Patterns[index].move[1];
					position.z = Patterns[index].move[2];
					return position;
				}
				if (CModelInfo::IsBoatModel(Patterns[index].chosen) && Patterns[index].moveType[x] == "boat")
				{
					position.x = Patterns[index].move[0];
					position.y = Patterns[index].move[1];
					position.z = Patterns[index].move[2];
					return position;
				}
			}
			return position;
		}
		// Move otherwise
		position.x = Patterns[index].move[0];
		position.y = Patterns[index].move[1];
		position.z = Patterns[index].move[2];
		return position;
	}
	// If the pattern doesn't have coordinates
	for (int i = 0; i < Patterns.size(); i++)
	{
		if (Patterns[i].vehicle == origModel)
		{
			if (Patterns[i].allowedType.size() > 0)
			{
				for (int x = 0; x < Patterns[i].moveType->size(); x++)
				{
					// Only added heli for now as it's the current only move type
					if (IsHeliModel(Patterns[i].chosen) && Patterns[i].moveType[x] == "heli")
					{
						position.x = Patterns[i].move[0];
						position.y = Patterns[i].move[1];
						position.z = Patterns[i].move[2];
						return position;
					}
					return position;
				}
			}
		}
	}
	return position;
}
std::vector<int> Script::ProcessVehicleTypes(Pattern pattern)
{
	std::vector<int> output;

	if (pattern.allowedType.size() > 0)
	{
		for (int x = 0; x < pattern.allowedType.size(); x++)
		{
			if (pattern.allowedType[x] == "car")
			{
				for (int model = 130; model < 237; model++)
				{
					if (IsCarModel(model))
						output.push_back(model);
				}
			}
			if (pattern.allowedType[x] == "bike")
			{
				for (int model = 130; model < 237; model++)
				{
					if (CModelInfo::IsBikeModel(model))
						output.push_back(model);
				}
			}
			if (pattern.allowedType[x] == "heli")
			{
				for (int model = 130; model < 237; model++)
				{
					if (IsHeliModel(model))
						output.push_back(model);
				}
			}
			if (pattern.allowedType[x] == "boat")
			{
				for (int model = 130; model < 237; model++)
				{
					if (CModelInfo::IsBoatModel(model))
						output.push_back(model);
				}
			}
			if (pattern.allowedType[x] == "rc")
			{
				for (int model = 130; model < 237; model++)
				{
					if (IsRCModel(model))
						output.push_back(model);
				}
			}
		}
	}
	return output;
}
void Script::Initialise()
{
	if (Config::script.Enabled)
	{
		plugin::patch::RedirectCall(0x44A1FD, ScriptVehicleRandomizer);
		plugin::patch::RedirectCall(0x42AEB0, CreateRandomizedCab);
		plugin::patch::RedirectCall(0x445267, FixForcedPlayerVehicleType);
		plugin::patch::RedirectCall(0x445202, FixForcedPedVehicleType);
		plugin::patch::RedirectCall(0x4536A0, FixTrojanVoodooForcedVehicle);
		plugin::patch::RedirectCall(0x44AA20, FixBombsAwayVan);
		plugin::patch::RedirectCall(0x45D435, FixBombsAwayBombPosition);
		plugin::patch::RedirectCall(0x6316CE, OpenBootFix);
		plugin::patch::SetChar(0x59EF9A, 1); // Unlock police vehicle doors

		if (Patterns.size() == 0)
			InitialisePatterns();
	}

	// Additional necessary fixes
	plugin::patch::RedirectCall(0x458A57, FixFrozenLoadingScreens);

	for (int addr : {0x428769, 0x4402C7, 0x440401, 0x440544, 0x44058E,
		0x455ABE, 0x47EE06, 0x485B5E, 0x4D286F, 0x4E2B86,
		0x4E2D51, 0x4E2E9B, 0x4E2FE1, 0x4E3289, 0x4E3454,
		0x4E359A, 0x509ABC, 0x509BB3, 0x509D25, 0x585C43,
		0x58ECFA, 0x59A3DC, 0x59A56C, 0x5A169D, 0x5A34BA,
		0x5A404A, 0x5A4873, 0x5A9F72, 0x5AA654, 0x5AA7D0,
		0x5AACE4, 0x5B352C, 0x5CA00B, 0x614017, 0x638465})
		plugin::patch::RedirectCall(addr, FixWaterLevelCrash);
}