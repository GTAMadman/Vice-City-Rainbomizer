#include "Parked.h"

void __fastcall Parked::ParkedVehiclesRandomizer(CCarGenerator* gen)
{
	int oldModel = gen->m_nModelId;
	int newModel;

	// Squalo at the Boatyard - only allow it to be a boat
	if (oldModel == 176)
	{
		while ((newModel = RandomNumber(130, 236)), !CModelInfo::IsBoatModel(newModel));

		gen->m_nModelId = (eVehicleModel)newModel;
		gen->DoInternalProcessing();
		return;
	}

	// Randomize any type of vehicle
	while ((newModel = RandomNumber(130, 236)), ModelInfo::IsBlacklistedVehicle(newModel));

	gen->m_nModelId = (eVehicleModel)newModel;
	gen->DoInternalProcessing();
}
void* __fastcall Parked::CarparkVehiclesRandomizer(CVehicle* vehicle, void* edx, int model, char createdBy)
{
	int newModel;

	while ((newModel = CStreaming::ms_vehiclesLoaded[RandomNumber(0, *ms_numVehiclesLoaded - 1)],
		ModelInfo::IsBlacklistedVehicle(newModel)) || newModel < 130 || newModel > 236);

	if (CModelInfo::IsBoatModel(newModel))
		reinterpret_cast<CBoat*>(vehicle)->CBoat::CBoat(newModel, createdBy);

	if (CModelInfo::IsPlaneModel(newModel))
		reinterpret_cast<CPlane*>(vehicle)->CPlane::CPlane(newModel, createdBy);

	if (CModelInfo::IsHeliModel(newModel))
		reinterpret_cast<CHeli*>(vehicle)->CHeli::CHeli(newModel, createdBy);

	if (CModelInfo::IsBikeModel(newModel))
		reinterpret_cast<CBike*>(vehicle)->CBike::CBike(newModel, createdBy);

	if (CModelInfo::IsCarModel(newModel))
		reinterpret_cast<CAutomobile*>(vehicle)->CAutomobile::CAutomobile(newModel, createdBy);

	// if the vehicle isn't loaded, return a police car
	if (CStreaming::ms_aInfoForModel[newModel].m_nLoadState != 1)
	{
		newModel = 156;
		reinterpret_cast<CAutomobile*>(vehicle)->CAutomobile::CAutomobile(newModel, createdBy);
	}
	return vehicle;
}
void Parked::Initialise()
{
	if (Config::parked.Enabled)
	{
		plugin::patch::RedirectCall(0x5A7163, ParkedVehiclesRandomizer);
		plugin::patch::RedirectCall(0x45A7B9, CarparkVehiclesRandomizer);
		plugin::patch::RedirectCall(0x45A78C, CarparkVehiclesRandomizer);
	}
}
