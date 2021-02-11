#include "Cutscenes.h"
#include "plugin.h"
#include "CModelInfo.h"

bool Cutscenes::DataFileExists = false;
const char* Cutscenes::GetRandomModel(char* model)
{
	if (Config::cutscene.Enabled && DataFileExists)
	{
		for (const auto& i : mModels)
		{
			if (DoesElementExist(i, model))
				return GetRandomElement(i).c_str();
		}
	}
	if (Config::ped.Enabled)
	{
		if (IsPedModel(model))
			return Ped::ped_models[RandomNumber(0, Ped::ped_models.size() - 1)].c_str();
	}

	return model;
}
bool Cutscenes::IsPedModel(char* model)
{
	if (Player::special_models.size() > 0)
	{
		for (std::string item : Player::special_models)
		{
			if (std::string(model) == item)
				return true;
		}
	}
	return false;
}
void Cutscenes::RequestSpecialModel(int modelId, const char* modelName, int flags)
{
	plugin::Call<0x40AA60>(modelId, modelName, flags);
}
void Cutscenes::RandomizeSpecialModelToLoad(int modelId, char* modelName, int flags)
{
	const char* model = GetRandomModel(modelName);

	RequestSpecialModel(modelId, model, flags);

	CStreaming::LoadAllRequestedModels(false);
	strncpy(CModelInfo::GetModelInfo(modelId)->m_szName, modelName, 21);
}
bool Cutscenes::InitialiseModelData()
{
	std::string fileDir = GetRainbomizerDir() + "CutsceneModels.txt";

	FILE* modelsFile = fopen(fileDir.c_str(), "r");
	mModels.clear();

	if (!modelsFile)
		return false;

	char line[512] = { 0 };
	mModels.push_back({});
	while (fgets(line, 512, modelsFile))
	{
		if (strlen(line) < 2)
		{
			mModels.push_back({});
			continue;
		}

		line[strcspn(line, "\n")] = 0;
		mModels.back().push_back(line);
	}

	return true;
}
void Cutscenes::Initialise()
{
	if (Config::cutscene.Enabled || Config::ped.Enabled)
	{
		plugin::patch::RedirectCall(0x409A42, RandomizeSpecialModelToLoad);
		plugin::patch::RedirectCall(0x4565D2, RandomizeSpecialModelToLoad);

		DataFileExists = InitialiseModelData();
	}
}