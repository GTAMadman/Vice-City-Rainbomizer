#pragma once
#include "CCutsceneObject.h"
#include <vector>
#include <string>
#include "Functions.h"
#include "Player.h"
#include "Ped.h"

struct CCutsceneObject_vftable;

class Cutscenes : Functions
{
private:
	static void RandomizeSpecialModelToLoad(int	modelId, char* modelName, int flags);
	static const char* GetRandomModel(char* model);
	static bool IsPedModel(char* model);
	inline static std::vector<std::vector<std::string>> mModels;
	static void RequestSpecialModel(int modelId, const char* modelName, int flags);
	static bool InitialiseModelData();
	static bool DataFileExists;
public:
	static void Initialise();
};