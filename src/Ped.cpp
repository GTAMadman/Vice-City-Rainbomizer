#include "Ped.h"

std::vector<std::string> Ped::ped_models;
std::unordered_map<int, int> vice_models =
{
	{0, 97}, {1, 98}, {2, 99}, {3, 100}, {4, 101}, {5, 102}, {6, 103}, {7, 104},
};

void Ped::ChooseRandomPedToLoad(int modelId, int flags)
{
	int newModel = 0;
	for (int i = 0; i < 21; i++)
	{
		newModel = GetRandomGenericPedBasedOnModel(modelId, true);
		if (!IsModelLoaded(newModel))
		{
			CStreaming::RequestModel(newModel, 0);
			return;
		}
	}
	CStreaming::RequestModel(modelId, 0);
}
void* __fastcall Ped::RandomizeGenericPeds(CCivilianPed* ped, void* edx, ePedType type, int model)
{
	int newModel = 0;

	for (int i = 0; i < 21; i++)
	{
		newModel = GetRandomGenericPedBasedOnModel(model, false);
		if (IsModelLoaded(newModel))
			break;
	}

	if (!IsModelLoaded(newModel) || IsSpecialModel(model) || IsRampageRunning())
		newModel = model;

	ped->CCivilianPed::CCivilianPed(type, newModel);
	return ped;
}
void* __fastcall Ped::RandomizeAndFixStreetPeds(CCivilianPed* ped, void* edx, ePedType type, int model)
{
	int newModel = model;

	if (Config::ped.genericPeds)
	{
		if (!IsRampageRunning())
		{
			for (int i = 0; i < 21; i++)
			{
				newModel = GetRandomGenericPedBasedOnModel(model, false);
				if (IsModelLoaded(newModel))
					break;
				else
					if (i != 20)
						continue;
					else
					{
						newModel = 0;
						break;
					}
			}
		}
		if (!IsModelLoaded(newModel))
			newModel = model;
	}

	if (IsSpecialModel(newModel))
	{
		if (Config::ped.genericPeds)
			newModel = GetRandomGenericPedBasedOnModel(0, false);
		else
			if (IsModelLoaded(7))
				newModel = 7;
			else
				newModel = 0;
	}

	ped->CCivilianPed::CCivilianPed(type, newModel);
	return ped;
}
void* __fastcall Ped::RandomizeCopPeds(CCopPed* ped, void* edx, eCopType type, int viceNum)
{
	eCopType newType;
	int random = RandomNumber(1, 5);
	int origViceNum = viceNum;

	switch (random)
	{
	case 1:
		newType = eCopType::COP_TYPE_COP;
		break;
	case 2:
		newType = eCopType::COP_TYPE_SWAT1;
		break;
	case 3:
		newType = eCopType::COP_TYPE_FBI;
		break;
	case 4:
		newType = eCopType::COP_TYPE_ARMY;
		break;
	case 5:
		newType = eCopType::COP_TYPE_VICE;
		break;
	}

	if (newType == eCopType::COP_TYPE_VICE)
	{
		viceNum = RandomNumber(0, 7);
		random = vice_models.at(viceNum);
	}

	LoadModel(random);

	if (!IsModelLoaded(random) || type == eCopType::COP_TYPE_SWAT2
		|| IsMission("protec3") && type == eCopType::COP_TYPE_COP)
	{
		newType = type;
		viceNum = origViceNum;
	}

	ped->CCopPed::CCopPed(newType, viceNum);
	return ped;
}
int Ped::GetRandomGenericPedBasedOnModel(int model, bool ignoreChecks)
{
	int newModel;

	if (!ignoreChecks)
	{
		// Cannon Fodder & Trojan Voodoo Fix
		if (model == 85 || model == 86)
		{
			if (IsMission("cuban2") || IsMission("cuban4"))
			{
				while ((newModel = RandomNumber(0, 106)), newModel == 8
					|| newModel == 83 || newModel == 84);

				return newModel;
			}
		}
	}

	if (Config::ped.forcedPed >= 0 && Config::ped.forcedPed <= 106)
		return Config::ped.forcedPed;

	while ((newModel = RandomNumber(0, 106)), newModel == 8);
	return newModel;
}
bool Ped::IsSpecialModel(int model)
{
	if (model >= 109 && model <= 129)
		return true;
	return false;
}
void Ped::Initialise()
{
	if (Config::ped.Enabled)
	{
		ped_models = Player::special_models;
		if (Config::ped.playerModels)
		{
			for (std::string item : Player::player_outfits)
				ped_models.push_back(item);
		}

		if (Config::ped.genericPeds)
		{
			for (int addr : {0x40A4F2, 0x40A35F})
				plugin::patch::RedirectCall(addr, ChooseRandomPedToLoad);

			for (int addr : {0x445EDF, 0x4496E0, 0x4529BF, 0x45E050,
				0x603D0C, 0x60464E, 0x621776})
				plugin::patch::RedirectCall(addr, RandomizeGenericPeds);
		}

		if (Config::ped.copPeds)
		{
			for (int addr : {0x4440A8, 0x4440CA, 0x445E8B, 0x449685, 0x45296B,
				0x53B731, 0x633107})
				plugin::patch::RedirectCall(addr, RandomizeCopPeds);
		}

		for (int addr : {0x53B63C, 0x53B8D8, 0x53B9ED})
			plugin::patch::RedirectCall(addr, RandomizeAndFixStreetPeds);
	}
}