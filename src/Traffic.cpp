#include "Traffic.h"

int Traffic::ChooseModelToLoad()
{
	int model;

	// Forced vehicles
	if (Config::traffic.forceVehicle)
		return Config::traffic.forcedVehicleID;

	for (int i = 0; i < 21; i++)
	{
		model = RandomNumber(130, 236);
		if (!IsVehicleAllowed(model) && !IsModelLoaded(model))
			continue;

		return model;
	}
	return -1;
}
int Traffic::RandomizeTraffic()
{
	int model;

	// Forced vehicles
	if (Config::traffic.forceVehicle)
	{
		model = Config::traffic.forcedVehicleID;
		if (!IsModelLoaded(model))
			LoadModel(model);

		return model;
	}

	if (GetNumberOfVehiclesLoaded() < 1) // Added as a safety precaution
		return -1;

	// Attempt to get a loaded vehicle 20 times - otherwise return nothing
	for (int i = 0; i < 21; i++)
	{
		model = GetRandomLoadedVehicle();
		if (!IsVehicleAllowed(model) || ModelInfo::IsBlacklistedVehicle(model) 
			 || model < 130 || model > 236 && IsModelLoaded(model))
			continue;

		return model;
	}
	return -1;
}
int Traffic::RandomizePoliceTraffic()
{
	int model;
	if (GetNumberOfVehiclesLoaded() < 1) // Added as a safety precaution
		return 156;

	for (int i = 0; i < 21; i++)
	{
		model = GetRandomLoadedVehicle();
		if (!IsVehicleAllowed(model) || ModelInfo::IsBlacklistedVehicle(model) 
			 || model < 130 || model > 236 && IsModelLoaded(model))
			continue;

		return model;
	}
	return 156;
}
void __fastcall Traffic::PedEnterCar(CPed* ped, void* edx)
{
	if (ModelInfo::IsRCModel(ped->m_pVehicle->m_nModelIndex))
	{
		if (Config::rc.DriveRCVehiclesEnabled)
			ped->IsPlayer() ? ped->WarpPedIntoCar(ped->m_pVehicle) : ped->QuitEnteringCar();
		else
			ped->QuitEnteringCar();
	}
	else
		ped->EnterCar();
}
void __fastcall Traffic::PedExitCar(CPed* ped, void* edx)
{
	if (ModelInfo::IsRCModel(ped->m_pVehicle->m_nModelIndex))
	{
		// Teleport the ped out
		ped->m_bInVehicle = false;
		CVector posn = ped->GetPosition();
		posn.z += 2;
		ped->Teleport(posn);
	}
	else
		ped->ExitCar();
}
void __fastcall Traffic::SetExitCar(CPed* ped, void* edx, CVehicle* vehicle, int value)
{
	if (ped->IsPlayer() && ModelInfo::IsRCModel(vehicle->m_nModelIndex))
	{
		ped->SetExitCar(vehicle, 1);
		return;
	}
	ped->SetExitCar(vehicle, value);
}
int __fastcall Traffic::FixPedKilledInRCVehicle(CPed* ped, void* edx)
{
	if (ModelInfo::IsRCModel(ped->m_pVehicle->m_nModelIndex))
		return 0;
	return ped->BeingDraggedFromCar();
}
bool Traffic::FixDeadPedsInFrontOfRCVehicles(int modelID)
{
	if (ModelInfo::IsRCModel(modelID) || CModelInfo::IsBoatModel(modelID))
		return false;
	return true;
}
void* Traffic::RandomizeCarPeds(ePedType type, int model, CVector& posn, int arg3)
{
	switch (type)
	{
	case 16:
		model = 5;
		break;
	case 17:
		model = 6;
		break;
	}

	switch (model)
	{
	case 1:
	case 3:
		model = 0;
		break;
	}
	int loadModel = model;

	if (!IsModelLoaded(loadModel))
		LoadModel(loadModel);

	return CPopulation::AddPed(type, model, posn, arg3);
}
void* __fastcall Traffic::RandomizeRoadblocks(CVehicle* vehicle, void* edx, int model, char createdBy)
{
	int newModel = model;

	if (GetNumberOfVehiclesLoaded() > 0)
	{
		for (int i = 0; i < 21; i++)
		{
			newModel = GetRandomLoadedVehicle();
			if (ModelInfo::IsMiscVehicle(newModel) || newModel < 130 || newModel > 236
				|| ModelInfo::IsBlacklistedVehicle(newModel) && IsModelLoaded(model))
				continue;

			break;
		}

		// Additional check just in case the loop ended with an invalid model
		if (ModelInfo::IsMiscVehicle(newModel) || newModel < 130 || newModel > 236
			|| ModelInfo::IsBlacklistedVehicle(newModel))
			newModel = model;
	}

	if (ModelInfo::IsBoatModel(newModel))
		reinterpret_cast<CBoat*>(vehicle)->CBoat::CBoat(newModel, createdBy);

	if (CModelInfo::IsPlaneModel(newModel))
		reinterpret_cast<CPlane*>(vehicle)->CPlane::CPlane(newModel, createdBy);

	if (CModelInfo::IsHeliModel(newModel))
		reinterpret_cast<CHeli*>(vehicle)->CHeli::CHeli(newModel, createdBy);

	if (CModelInfo::IsBikeModel(newModel))
		reinterpret_cast<CBike*>(vehicle)->CBike::CBike(newModel, createdBy);

	if (!IsModelLoaded(newModel))
		newModel = 156;

	if (CModelInfo::IsCarModel(newModel))
		reinterpret_cast<CAutomobile*>(vehicle)->CAutomobile::CAutomobile(newModel, createdBy);

	vehicle->m_nState = eEntityStatus::STATUS_PHYSICS;

	return vehicle;
}
void* __fastcall Traffic::FixTrafficVehicles(CVehicle* vehicle, void* edx, int model, char createdBy)
{
	if (ModelInfo::IsMiscVehicle(model))
	{
		reinterpret_cast<CBoat*>(vehicle)->CBoat::CBoat(model, createdBy);
		return vehicle;
	}

	if (ModelInfo::IsBoatModel(model))
		reinterpret_cast<CBoat*>(vehicle)->CBoat::CBoat(model, createdBy);

	if (CModelInfo::IsPlaneModel(model))
		reinterpret_cast<CPlane*>(vehicle)->CPlane::CPlane(model, createdBy);

	if (CModelInfo::IsHeliModel(model))
		reinterpret_cast<CHeli*>(vehicle)->CHeli::CHeli(model, createdBy);

	if (CModelInfo::IsBikeModel(model))
		reinterpret_cast<CBike*>(vehicle)->CBike::CBike(model, createdBy);

	if (CModelInfo::IsCarModel(model))
		reinterpret_cast<CAutomobile*>(vehicle)->CAutomobile::CAutomobile(model, createdBy);


	if (vehicle->m_nModelIndex == 156)
	{
		vehicle->ChangeLawEnforcerState(1);
		vehicle->m_nLockStatus = 5;
	}

	return vehicle;
}
void Traffic::AddPoliceCarOccupants(CVehicle* vehicle)
{
	plugin::CallDynGlobal<CVehicle*>(0x419BB0, vehicle);
}
void Traffic::FixEmptyPoliceCars(CVehicle* vehicle)
{
	int origModel = vehicle->m_nModelIndex;
	vehicle->m_nModelIndex = 156;

	AddPoliceCarOccupants(vehicle);
	vehicle->m_nModelIndex = origModel;
}
void Traffic::FixBoatSpawns(CPhysical* entity)
{
	if (CModelInfo::IsBoatModel(entity->m_nModelIndex) || ModelInfo::IsEmergencyVehicle(entity->m_nModelIndex))
	{
		CVector posn = entity->GetPosition();
		switch (entity->m_nModelIndex)
		{
		case 184:
			posn.z += 0.6f;
			break;
		case 183:
		case 202:
		case 160:
		case 182:
			posn.z += 0.5f;
			break;
		case 214:
			posn.z += 1.5f;
			break;
		case 190:
			posn.z += 2;
			break;
		case 176:
			posn.z += 0.9f;
			break;
		case 136:
		case 223:
			posn.z++;
			break;
		}
		entity->SetPosition(posn);
		entity->m_nState = eEntityStatus::STATUS_PHYSICS;
	}
	CWorld::Add(entity);
}
bool Traffic::IsVehicleAllowed(int model)
{
	if (model < 130 || model > 236)
		return false;

	if (model == 180 && Config::traffic.airTrain)
		return true;

	if (model == 181 && Config::traffic.deadDodo)
		return true;

	if (ModelInfo::IsCarModel(model) && Config::traffic.cars)
		return true;

	if (CModelInfo::IsBikeModel(model) && Config::traffic.bikes)
		return true;

	if (ModelInfo::IsRCModel(model) && Config::traffic.RC)
		return true;

	if (ModelInfo::IsBoatModel(model) && Config::traffic.boats)
		return true;

	if (ModelInfo::IsHeliModel(model) && Config::traffic.helis)
		return true;

	return false;
}
void __fastcall Traffic::FixRoadblockCrash(CMatrix* matrix)
{
	if (!matrix)
		return;

	matrix->UpdateRW();
}
void Traffic::Initialise()
{
	if (Config::traffic.Enabled)
	{
		plugin::patch::RedirectCall(0x426FA6, RandomizeTraffic);
		plugin::patch::RedirectCall(0x426F80, RandomizePoliceTraffic);
		plugin::patch::RedirectCall(0x426BA4, RandomizePoliceTraffic);
		plugin::patch::RedirectCall(0x4098D3, ChooseModelToLoad);
		plugin::patch::RedirectCall(0x42773A, FixTrafficVehicles);
		plugin::patch::RedirectCall(0x53AC31, RandomizeCarPeds);
		plugin::patch::RedirectCall(0x428D96, FixEmptyPoliceCars);
		plugin::patch::RedirectCall(0x428FC8, FixDeadPedsInFrontOfRCVehicles);
		plugin::patch::RedirectCall(0x428D7B, FixBoatSpawns);

		if (Config::traffic.scriptedCopCarsEnabled)
		{
			plugin::patch::RedirectCall(0x633213, RandomizeRoadblocks);
			for (int addr : {0x6334CE, 0x63368A, 0x6337CB, 0x633AFB, 0x633C11,
				0x633D4A, 0x633E60})
				plugin::patch::RedirectCall(addr, FixEmptyPoliceCars);
		}
		if (Config::traffic.roadblocksEnabled)
			plugin::patch::RedirectCall(0x443924, RandomizeRoadblocks);
	}
	/* RC Vehicles Fixes - initialise these even without traffic being enabled
	in case something else is enabled which can spawn RC vehicles */
	plugin::patch::RedirectCall(0x4D7AD8, PedExitCar);
	plugin::patch::RedirectCall(0x4D7AB2, PedEnterCar);
	plugin::patch::RedirectCall(0x4D7ACF, FixPedKilledInRCVehicle);
	plugin::patch::RedirectCall(0x4D7AC4, FixPedKilledInRCVehicle);
	plugin::patch::RedirectCall(0x53D2C1, FixRoadblockCrash);
	for (int addr : {0x51DD88, 0x51DEEA, 0x51DFD1})
		plugin::patch::RedirectCall(addr, SetExitCar);
}