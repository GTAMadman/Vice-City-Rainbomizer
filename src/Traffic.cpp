#include "Traffic.h"

int* Traffic::ms_numVehiclesLoaded = reinterpret_cast<int*>(0xA10858);
int Traffic::ChooseModelToLoad()
{
	/* Loads a random vehicle model into memory */
	int newModel;
	while ((newModel = RandomNumber(130, 236)), ModelInfo::IsBlacklistedVehicle(newModel))

	return newModel;
}
int Traffic::ChooseModel()
{
	/* From the randomly loaded vehicles, this will choose a model to spawn in traffic */
	int model;

	if (*ms_numVehiclesLoaded < 3) // Added as a safety precaution
		return -1;

	while ((model = CStreaming::ms_vehiclesLoaded[RandomNumber(0, *ms_numVehiclesLoaded - 1)],
		ModelInfo::IsBlacklistedVehicle(model)) || model < 130 || model > 236);

	if (CStreaming::ms_aInfoForModel[model].m_nLoadState != 1)
		return -1;

	return model;
}
int Traffic::ChoosePoliceModel()
{
	int model;

	if (*ms_numVehiclesLoaded < 3) // Added as a safety precaution
		return 156;

	while ((model = CStreaming::ms_vehiclesLoaded[RandomNumber(0, *ms_numVehiclesLoaded - 1)],
		ModelInfo::IsBlacklistedVehicle(model)));

	if (CStreaming::ms_aInfoForModel[model].m_nLoadState != 1)
		return 156;

	return model;
}
void __fastcall Traffic::PedEnterCar(CPed* ped, void* edx)
{
	if (ModelInfo::IsRCModel(ped->m_pVehicle->m_nModelIndex))
	{
		if (Config::RCVehiclesRandomizer::DriveRCVehiclesEnabled)
		{
			if (ped->IsPlayer())
				ped->WarpPedIntoCar(ped->m_pVehicle);
			else
				ped->QuitEnteringCar();
		}
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
	/* Fix peds who are killed inside RC vehicles */
	if (ModelInfo::IsRCModel(ped->m_pVehicle->m_nModelIndex))
		return 0;

	return ped->BeingDraggedFromCar();
}
void* Traffic::RandomizeCarPeds(ePedType type, int model, CVector posn, int arg3)
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

	while (CStreaming::ms_aInfoForModel[loadModel].m_nLoadState != 1)
		LoadModel(loadModel);

	return CPopulation::AddPed(type, model, posn, arg3);
}
void* __fastcall Traffic::FixTrafficVehicles(CVehicle* vehicle, void* edx, int model, char createdBy)
{
	if (CModelInfo::IsBoatModel(model))
		reinterpret_cast<CBoat*>(vehicle)->CBoat::CBoat(model, createdBy);

	if (CModelInfo::IsPlaneModel(model))
		reinterpret_cast<CPlane*>(vehicle)->CPlane::CPlane(model, createdBy);

	if (CModelInfo::IsHeliModel(model))
		reinterpret_cast<CHeli*>(vehicle)->CHeli::CHeli(model, createdBy);

	if (CModelInfo::IsBikeModel(model))
		reinterpret_cast<CBike*>(vehicle)->CBike::CBike(model, createdBy);

	if (CModelInfo::IsCarModel(model))
		reinterpret_cast<CAutomobile*>(vehicle)->CAutomobile::CAutomobile(model, createdBy);

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
	if (CModelInfo::IsBoatModel(entity->m_nModelIndex))
	{
		CVector posn = entity->GetPosition();
		switch (entity->m_nModelIndex)
		{
		case 214:
			posn.z += 1.5f;
			break;
		case 190:
			posn.z += 2;
			break;
		case 223:
			posn.z++;
			break;
		case 176:
			posn.z++;
		}
		entity->SetPosition(posn);
	}
	CWorld::Add(entity);
}

void Traffic::Initialise()
{
	if (Config::TrafficRandomizer::Enabled)
	{
		plugin::patch::RedirectCall(0x426FA6, ChooseModel);
		plugin::patch::RedirectCall(0x426F80, ChoosePoliceModel);
		plugin::patch::RedirectCall(0x4098D3, ChooseModelToLoad);
		plugin::patch::RedirectCall(0x42773A, FixTrafficVehicles);
		plugin::patch::RedirectCall(0x53AC31, RandomizeCarPeds);
		plugin::patch::RedirectCall(0x428D96, FixEmptyPoliceCars);
		plugin::patch::RedirectCall(0x428D7B, FixBoatSpawns);
	}
	// RC Vehicles Fixes - initialise these without checks
	plugin::patch::RedirectCall(0x4D7AD8, PedExitCar);
	plugin::patch::RedirectCall(0x4D7AB2, PedEnterCar);
	plugin::patch::RedirectCall(0x4D7ACF, FixPedKilledInRCVehicle);
	plugin::patch::RedirectCall(0x4D7AC4, FixPedKilledInRCVehicle);
	for (int addr : {0x51DD88, 0x51DEEA, 0x51DFD1})
		plugin::patch::RedirectCall(addr, SetExitCar);
}