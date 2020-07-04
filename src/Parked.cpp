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
		gen->m_nModelId = (eVehicleModel)oldModel;
		return;
	}

	// Randomize any type of vehicle
	while ((newModel = RandomNumber(130, 236)), ModelInfo::IsMiscVehicle(newModel)
		|| ModelInfo::IsBlacklistedVehicle(newModel));

	gen->m_nModelId = (eVehicleModel)newModel;

	gen->DoInternalProcessing();
	gen->m_nModelId = (eVehicleModel)oldModel;
}
void* __fastcall Parked::CarparkVehiclesRandomizer(CVehicle* vehicle, void* edx, int model, char createdBy)
{
	int newModel;
	for (int i = 0; i < 21; i++)
	{
		newModel = CStreaming::ms_vehiclesLoaded[RandomNumber(0, *ms_numVehiclesLoaded - 1)];
		if (ModelInfo::IsMiscVehicle(newModel) || ModelInfo::IsBlacklistedVehicle(newModel)
			|| newModel < 130 || newModel > 236)
			continue;

		if (!IsModelLoaded(newModel))
			newModel = model;
	}

	// Additional check just in case the loop ended with an invalid model
	if (ModelInfo::IsMiscVehicle(newModel) || ModelInfo::IsBlacklistedVehicle(newModel)
		|| newModel < 130 || newModel > 236 || !IsModelLoaded(newModel))
		newModel = model;

	if (ModelInfo::IsBoatModel(newModel))
		reinterpret_cast<CBoat*>(vehicle)->CBoat::CBoat(newModel, createdBy);

	if (CModelInfo::IsPlaneModel(newModel))
		reinterpret_cast<CPlane*>(vehicle)->CPlane::CPlane(newModel, createdBy);

	if (CModelInfo::IsHeliModel(newModel))
		reinterpret_cast<CHeli*>(vehicle)->CHeli::CHeli(newModel, createdBy);

	if (CModelInfo::IsBikeModel(newModel))
		reinterpret_cast<CBike*>(vehicle)->CBike::CBike(newModel, createdBy);

	if (CModelInfo::IsCarModel(newModel))
		reinterpret_cast<CAutomobile*>(vehicle)->CAutomobile::CAutomobile(newModel, createdBy);

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