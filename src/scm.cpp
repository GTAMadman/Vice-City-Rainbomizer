#include "scm.h"

std::vector<scm::Pattern> scm::Patterns;
std::vector<int> scm::AlloyWheelsVehicles;
void __fastcall scm::ScriptVehicleRandomizer(CRunningScript* thisScript, void* edx, int* arg0, short count)
{
	thisScript->CollectParameters(arg0, count);

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
		newModel = GetIDBasedOnPattern(origModel, x, y, z, thisScript->m_szName);

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
	AlloyWheelsFix(newModel, thisScript->m_szName);
}
void scm::FixForcedPlayerVehicleType(CRunningScript* thisScript, void* edx, int* arg0, short count)
{
	thisScript->CollectParameters(arg0, count);
	int origModel = CTheScripts::ScriptParams[1].iParam;

	// Alloy Wheels of Steal
	if (thisScript->m_szName == (std::string)"bike1" && origModel == 193 || origModel == 166)
	{
		if (FindPlayerVehicle())
			CTheScripts::ScriptParams[1].iParam = FindPlayerVehicle()->m_nModelIndex;
	}
	// Dirtring
	if (thisScript->m_szName == (std::string)"kickst" && origModel == 198)
	{
		if (FindPlayerVehicle())
		CTheScripts::ScriptParams[1].iParam = FindPlayerVehicle()->m_nModelIndex;
	}
	// Kaufman Cab Missions & Checkpoint Charie
	if (origModel == 216 || origModel == 176)
	{
		if (FindPlayerVehicle())
			CTheScripts::ScriptParams[1].iParam = FindPlayerVehicle()->m_nModelIndex;
	}
}
void scm::FixForcedPedVehicleType(CRunningScript* thisScript, void* edx, int* arg0, short count)
{
	thisScript->CollectParameters(arg0, count);
	int origModel = CTheScripts::ScriptParams[1].iParam;

	if (thisScript->m_szName == (std::string)"bike1" && origModel == 166)
	{
		CTheScripts::ScriptParams[1].iParam = AlloyWheelsVehicles[RandomNumber(0, AlloyWheelsVehicles.size() - 1)];
	}
}
void* __fastcall scm::CreateRandomizedCab(CVehicle* vehicle, void* edx, int modelId, bool createdBy)
{
	int newModel;

	while ((newModel = RandomNumber(130, 236)), ModelInfo::IsBlacklistedVehicle(newModel) || 
		ModelInfo::IsRCModel(newModel) || CModelInfo::IsBoatModel(newModel) || newModel == 155 ||
		newModel == 178 || newModel == 215); // Hunter, Pizza Boy, Baggage

	LoadModel(newModel);

	if (CModelInfo::IsHeliModel(newModel))
		reinterpret_cast<CHeli*>(vehicle)->CHeli::CHeli(newModel, createdBy);

	if (CModelInfo::IsBikeModel(newModel))
		reinterpret_cast<CBike*>(vehicle)->CBike::CBike(newModel, createdBy);

	if (CModelInfo::IsCarModel(newModel))
		reinterpret_cast<CAutomobile*>(vehicle)->CAutomobile::CAutomobile(newModel, createdBy);

	return vehicle;
}
void __fastcall scm::FixBombsAwayVan(CRunningScript* thisScript, void* edx, int* arg0, short count)
{
	thisScript->CollectParameters(arg0, count);

	/* As it resets the vehicle position, I have to change it here instead */
	if (thisScript->m_szName == (std::string)"hait2")
	{
		int x = CTheScripts::ScriptParams[1].fParam;
		int y = CTheScripts::ScriptParams[2].fParam;
		int z = CTheScripts::ScriptParams[3].fParam;

		if (x == -808 && y == -162 && z == 10)
			CTheScripts::ScriptParams[2].fParam += 15;
	}
}
void* __fastcall scm::OpenBootFix(CAutomobile* vehicle, void* edx)
{
	if (!vehicle->m_aCarNodes[18])
		return vehicle;

	vehicle->PopBoot();
	return vehicle;
}
void scm::AlloyWheelsFix(int modelID, char* thread)
{
	/* Checking for "Alloy Wheels of Steel" - this will store the bikes
	that the bikers are driving so they can go through checkpoints */
	if (thread == (std::string)"bike1")
		AlloyWheelsVehicles.push_back(modelID);
	else
		if (AlloyWheelsVehicles.size() > 0)
			AlloyWheelsVehicles.clear();
}
void scm::InitialisePatterns()
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
	pattern = { .vehicle = {171}, .allowed = {171}, .allowedType = {"car"} };
	Patterns.push_back(pattern);

	// RC Baron
	pattern = { .vehicle = {194}, .allowed = {194, 190, 195, 231}, .allowedType = {"heli"} };
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
	pattern = { .vehicle = {150}, .allowed = {167, 161}, .coords = {496, -84, 9}, .doors = {4} };
	Patterns.push_back(pattern);

	// Speeder - Stunt Boat Challenge
	pattern = { .vehicle = {182}, .allowed = {182, 202, 223, 160, 176, 190}, .coords = {-90, 105, 5} };
	Patterns.push_back(pattern);

	// Vigilante
	pattern = { .thread = {"copcar"}, .doors = {4} };
	Patterns.push_back(pattern);

	// Firefighter
	pattern = { .thread = {"firetru"} };
	Patterns.push_back(pattern); // Using thread only will return the original vehicle

	// Publicity Tour
	pattern = { .vehicle = {201}, .allowed = {167, 161}, .denied = {217, 227}, .coords = {-872, 1151, 11}, .doors = {4} };
	Patterns.push_back(pattern);

	// Phnom Penh '86 - Maverick
	pattern = { .vehicle = {217}, .allowedType = {"car", "heli", "rc"}, .thread = {"baron2"} };
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

	// Supply & Demand - Squalo
	pattern = { .vehicle = {176}, .denied = {190}, .allowedType = {"boat"}, .coords = {-378, -660, 5} };
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
	pattern = { .vehicle = {143}, .allowedType = {"car", "bike"}, .coords = {-1161, 76, 10}, .move = {-2, 0, 0} };
	Patterns.push_back(pattern);

	// Naval Engagement - Jetmax
	pattern = { .vehicle = {223}, .denied = {190}, .coords = {-722, -1163, 5} };
	Patterns.push_back(pattern);

	// Trojan Voodoo
	pattern = { .vehicle = {142}, .allowed = {142}, .coords = {-1071, -608, 9} };
	Patterns.push_back(pattern);

	// V.I.P - Taxi
	pattern = { .vehicle = {150}, .denied = {178, 215}, .coords = {-546, -474, 10} };
	Patterns.push_back(pattern);
}
/* I've only built the pattern system to work with the necessary patterns for the main game.
   Currently this isn't a great way to do it, but this may be changed in future. */
int scm::GetIDBasedOnPattern(int origModel, int x, int y, int z, char* thread)
{
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
				Patterns[index].doors > 0)
			{
				vehicles = Patterns[index].allowed;
				for (int model = 130; model < 237; model++)
				{
					if (CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(model) == Patterns[index].doors - 1)
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
			if (Patterns[index].doors > 0)
			{
				for (int model = 130; model < 237; model++)
				{
					if (CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(model) == Patterns[index].doors - 1)
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
	{
		int newModel = 0;
		while (!ModelInfo::IsCarModel(newModel))
			newModel = RandomNumber(130, 236);

		return newModel;
	}

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
CVector scm::CheckPatternForMovePosition(int origModel, int x, int y, int z)
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
std::vector<int> scm::ProcessVehicleTypes(Pattern pattern)
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
void scm::Initialise()
{
	if (Config::script.Enabled)
	{
		plugin::patch::RedirectCall(0x44A1FD, ScriptVehicleRandomizer);
		plugin::patch::RedirectCall(0x42AEB0, CreateRandomizedCab);
		plugin::patch::RedirectCall(0x445267, FixForcedPlayerVehicleType);
		plugin::patch::RedirectCall(0x445202, FixForcedPedVehicleType);
		plugin::patch::RedirectCall(0x44AA20, FixBombsAwayVan);
		plugin::patch::RedirectCall(0x6316CE, OpenBootFix);
		plugin::patch::SetChar(0x59EF9A, 1); // Unlock police vehicle doors

		if (Patterns.size() == 0)
		InitialisePatterns();
	}
}
