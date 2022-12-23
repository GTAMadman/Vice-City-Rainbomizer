#include "Config.h"

const std::string Config::ConfigName = Functions::GetRainbomizerDir() + "config.cfg";

void ReadConfigBool(const std::string& key, const std::string& data, bool& value)
{
	if (data.find(key) != std::string::npos)
		value = data.find("true") != std::string::npos;
}
void ReadConfigInt(const std::string& key, const std::string& data, int& value)
{
	if (data.find(key) != std::string::npos)
	{
		std::stringstream stream;
		stream << data;

		std::string str;
		int val;

		while (!stream.eof())
		{
			stream >> str;
			if (std::stringstream(str) >> val)
			{
				value = val;
				break;
			}
		}
	}
}
void ReadConfigString(const std::string& key, const std::string& data, std::string& value)
{
	if (data.find(key) != std::string::npos)
	{
		std::stringstream stream;
		std::string output;

		stream << data;

		std::getline(stream, output, '\"');
		while (!stream.eof())
		{
			std::getline(stream, output, '\"');
			stream.ignore(256, '\"');
		}
		value = output;
	}
}
void Config::General::Read(const std::string& line)
{
	ReadConfigBool("DisableReplays", line, replays);
	ReadConfigBool("ModifyCredits", line, credits);
	ReadConfigBool("EnableEasterEggs", line, easterEggs);
}
void Config::ScriptedVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("ScriptVehiclesRandomizer", line, Enabled);

	ReadConfigBool("OffroadMissions", line, offroadEnabled);
	ReadConfigBool("RCMissions", line, rcEnabled);
	ReadConfigBool("ChopperCheckpoints", line, chopperCheckpointEnabled);
	ReadConfigBool("PizzaBoy", line, pizzaBoyEnabled);

	ReadConfigInt("ForcedScriptVehicle", line, forcedVehicle);
}
void Config::RCVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("RandomizeRCVehicles", line, Enabled);
	ReadConfigBool("AllowPlayerToDriveRCVehicles", line, DriveRCVehiclesEnabled);
}
void Config::ParkedVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("ParkedVehiclesRandomizer", line, Enabled);
	ReadConfigInt("ForcedParkedVehicle", line, forcedVehicle);
}
void Config::ColourRandomizer::Read(const std::string& line)
{
	ReadConfigBool("RandomizeVehicleColours", line, vehicleEnabled);

	ReadConfigBool("RandomizeHUDColours", line, textEnabled);
	ReadConfigBool("RainbowHUDColours", line, rainbowTextEnabled);

	ReadConfigBool("RandomizeMarkerColours", line, markersEnabled);
	ReadConfigBool("StaticMarkerColours", line, staticMarkerColours);

	ReadConfigBool("RandomizePickupColours", line, pickupsEnabled);
	ReadConfigBool("StaticPickupColours", line, staticPickupColours);

	ReadConfigBool("RandomizeLazerScopeColour", line, lazerScopeEnabled);
	ReadConfigBool("StaticLazerScopeColours", line, staticLazerScopeColours);

	ReadConfigBool("RandomizeExplosionColours", line, explosionsEnabled);
	ReadConfigBool("StaticExplosionColours", line, staticExplosionColours);
}
void Config::TrafficRandomizer::Read(const std::string& line)
{
	ReadConfigBool("TrafficRandomizer", line, Enabled);
	ReadConfigBool("RandomizeScriptedCopCars", line, scriptedCopCarsEnabled);
	ReadConfigBool("RandomizeRoadblocks", line, roadblocksEnabled);

	ReadConfigBool("EnableCars", line, cars);
	ReadConfigBool("EnableBikes", line, bikes);
	ReadConfigBool("EnableRC", line, RC);
	ReadConfigBool("EnableBoats", line, boats);
	ReadConfigBool("EnableHelis", line, helis);

	ReadConfigBool("EnableDeadDodo", line, deadDodo);
	ReadConfigBool("EnableAirTrain", line, airTrain);

	ReadConfigInt("ForcedTrafficVehicle", line, forcedVehicle);
}
void Config::WeaponRandomizer::Read(const std::string& line)
{
	ReadConfigBool("WeaponRandomizer", line, Enabled);
	ReadConfigBool("RandomizePlayerWeapons", line, randomizePlayerWeapons);
	ReadConfigBool("RandomizeRampageWeapons", line, randomizeRampageWeapons);
	ReadConfigBool("ReduceMeleeWeapons", line, ReduceMeleeWeaponsEnabled);
	ReadConfigBool("AllowRocketMissile", line, RocketEnabled);
	ReadConfigBool("AllowTearGas", line, tearGasEnabled);
	ReadConfigInt("ForcedWeapon", line, forcedWeapon);
}
void Config::PickupsRandomizer::Read(const std::string& line)
{
	ReadConfigBool("PickupsRandomizer", line, Enabled);
	ReadConfigBool("RandomizePedWeaponDrops", line, randomizePedDrops);
	ReadConfigBool("RandomizeMetalDetectorWeapons", line, randomizeMetalDetectorWeps);

	ReadConfigBool("EnableWeapons", line, weapons);
	ReadConfigBool("EnableHealth", line, health);
	ReadConfigBool("EnableArmour", line, armour);
	ReadConfigBool("EnableAdrenaline", line, adrenaline);
	ReadConfigBool("EnableBribes", line, bribes);
	ReadConfigBool("EnableCellphone", line, cellphone);
	ReadConfigBool("EnableBriefcase", line, briefcase);
	ReadConfigBool("EnableKeycard", line, keycard);

	ReadConfigBool("MoneyInBriefcase", line, briefcaseMoney);
	ReadConfigString("PickupsCustomSeed", line, seed);

	ReadConfigInt("ForcedPickup", line, forcedPickup);

	if (seed != "")
		usingSeed = true;
}
void Config::PlayerRandomizer::Read(const std::string& line)
{
	ReadConfigBool("PlayerRandomizer", line, Enabled);

	ReadConfigBool("RandomizePlayerOutfits", line, playerOutfits);
	ReadConfigBool("IncludeSpecialModels", line, specialModels);

	ReadConfigBool("RandomizeOnFades", line, randomizeOnFades);
	ReadConfigString("ForcedPlayerModel", line, forcedModel);
}
void Config::PedRandomizer::Read(const std::string& line)
{
	ReadConfigBool("PedRandomizer", line, Enabled);

	ReadConfigBool("RandomizeSpecialModels", line, specialModels);
	ReadConfigBool("RandomizeGenericPeds", line, genericPeds);
	ReadConfigBool("RandomizeCopPeds", line, copPeds);

	ReadConfigBool("IncludePlayerModels", line, playerModels);
	ReadConfigInt("ForcedPedModel", line, forcedPed);
}
void Config::MissionRandomizer::Read(const std::string& line)
{
	ReadConfigBool("MissionRandomizer", line, Enabled);
	ReadConfigString("MissionCustomSeed", line, seed);
	ReadConfigInt("ForcedMission", line, forcedMission);

	if (seed != "")
		usingSeed = true;
}
void Config::CutsceneRandomizer::Read(const std::string& line)
{
	ReadConfigBool("CutsceneRandomizer", line, Enabled);
}
void Config::VoiceLineRandomizer::Read(const std::string& line)
{
	ReadConfigBool("VoiceLineRandomizer", line, Enabled);
	ReadConfigBool("MatchSubtitles", line, MatchSubtitles);
	ReadConfigBool("LoopPhoneRingtone", line, loopEnabled);
}
void Config::Autosave::Read(const std::string& line)
{
	ReadConfigBool("Autosave", line, Enabled);
	ReadConfigInt("Slot", line, slot);

	if (slot < 1 || slot > 8)
		slot = 8;
}
void Config::WriteConfig()
{
	std::ofstream config;
	config.open(ConfigName);
	config << default_config;
	config.close();
}
void Config::Initialise()
{
	if (!std::filesystem::exists(Functions::GetRainbomizerDir()))
		return;

	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	for (std::string str; std::getline(config, str); )
	{
		general.Read(str);
		script.Read(str);
		rc.Read(str);
		parked.Read(str);
		traffic.Read(str);
		weapons.Read(str);
		colours.Read(str);
		autosave.Read(str);
		voice.Read(str);
		pickups.Read(str);
		player.Read(str);
		ped.Read(str);
		cutscene.Read(str);
		mission.Read(str);
	}
}