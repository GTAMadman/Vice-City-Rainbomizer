#include "ModelInfo.h"

/* Due to having some issues with some functions for "CModelInfo" I decided
   to just create my own functions for some of the vehicles to prevent this. */
std::string ModelInfo::CheckVehicleModel(int modelID)
{
	if (IsCarModel(modelID))
		return "car";

	if (CModelInfo::IsBikeModel(modelID))
		return "bike";

	if (IsHeliModel(modelID))
		return "heli";

	if (CModelInfo::IsBoatModel(modelID))
		return "boat";

	if (IsRCModel(modelID))
		return "rc";

	return "unknown";
}
bool ModelInfo::IsBlacklistedVehicle(int modelID)
{
	if (modelID > 179 && modelID < 182 || modelID == 165)
		return true;
	return false;
}
bool ModelInfo::IsHeliModel(int modelID)
{
	switch (modelID)
	{
	case 155:
	case 177:
	case 199:
	case 217:
	case 218:
	case 227:
		return true;
	}
	return false;
}
bool ModelInfo::IsRCModel(int modelID)
{
	switch (modelID)
	{
	case 171: // RC Bandit
	case 194: // RC Baron
	case 195: // BRC Raider
	case 231: // RC Goblin
		return true;
	}
	return false;
}
bool ModelInfo::IsPoliceModel(int modelID)
{
	switch (modelID)
	{
	case 156:
	case 157:
	case 160:
	case 162:
	case 163:
	case 227:
	case 147:
	case 153: // Not a police vehicle but wanted to add it :P
		return true;
	}
	return false;
}
bool ModelInfo::IsCarModel(int modelID)
{
	if (modelID > 129 && modelID < 136)
		return true;

	if (modelID > 136 && modelID < 155)
		return true;

	if (modelID > 155 && modelID < 160)
		return true;

	if (modelID > 160 && modelID < 165)
		return true;

	if (modelID > 166 && modelID < 171)
		return true;

	if (modelID > 171 && modelID < 176)
		return true;

	if (modelID > 184 && modelID < 190)
		return true;

	if (modelID > 195 && modelID < 198)
		return true;

	if (modelID > 199 && modelID < 202)
		return true;

	if (modelID > 203 && modelID < 214)
		return true;

	if (modelID > 218 && modelID < 223)
		return true;

	if (modelID > 223 && modelID < 227)
		return true;

	if (modelID > 227 && modelID < 231)
		return true;

	if (modelID > 231 && modelID < 237)
		return true;

	if (modelID == 179 || modelID == 215 || modelID == 216)
		return true;

	if (IsBlacklistedVehicle(modelID))
		return false;
	return false;

}
