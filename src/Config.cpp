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
void Config::General::Read(const std::string& line)
{
	ReadConfigBool("DisableReplays", line, replays);
	ReadConfigBool("ModifyCredits", line, credits);
}
void Config::ScriptedVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("ScriptVehiclesRandomizer", line, Enabled);

	ReadConfigBool("OffroadMissions", line, offroadEnabled);
	ReadConfigBool("RCMissions", line, rcEnabled);
	ReadConfigBool("ChopperCheckpoints", line, chopperCheckpointEnabled);
	ReadConfigBool("PizzaBoy", line, pizzaBoyEnabled);
}
void Config::RCVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("RandomizeRCVehicles", line, Enabled);
	ReadConfigBool("AllowPlayerToDriveRCVehicles", line, DriveRCVehiclesEnabled);
}
void Config::ParkedVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("ParkedVehiclesRandomizer", line, Enabled);
}
void Config::ColourRandomizer::Read(const std::string& line)
{
	ReadConfigBool("RandomizeVehicleColours", line, vehicleEnabled);
	ReadConfigBool("RandomizeHUDColours", line, textEnabled);
	ReadConfigBool("RandomizeMarkerColours", line, markersEnabled);

	ReadConfigBool("RandomizePickupColours", line, pickupsEnabled);
	ReadConfigBool("RandomizeLazerScopeColour", line, lazerScopeEnabled);
	ReadConfigBool("RandomizeExplosionColours", line, explosionsEnabled);

	ReadConfigBool("RainbowHUDColours", line, rainbowTextEnabled);
	ReadConfigBool("VibrantStaticHUDColours", line, vibrantOnlyEnabled);
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

	ReadConfigInt("ForcedVehicleID", line, forcedVehicleID);

	if (forcedVehicleID > 129 && forcedVehicleID < 237)
		forceVehicle = true;
}
void Config::WeaponRandomizer::Read(const std::string& line)
{
	ReadConfigBool("WeaponRandomizer", line, Enabled);
	ReadConfigBool("ReduceMeleeWeapons", line, ReduceMeleeWeaponsEnabled);
	ReadConfigBool("AllowRocketMissile", line, RocketEnabled);
	ReadConfigBool("AllowTearGas", line, tearGasEnabled);
}
void Config::PickupsRandomizer::Read(const std::string& line)
{
	ReadConfigBool("PickupsRandomizer", line, Enabled);
	ReadConfigBool("RandomizePedWeaponDrops", line, randomizePedDrops);

	ReadConfigBool("EnableWeapons", line, weapons);
	ReadConfigBool("PEnableHealth", line, health);
	ReadConfigBool("EnableArmour", line, armour);
	ReadConfigBool("EnableAdrenaline", line, adrenaline);
	ReadConfigBool("EnableBribes", line, bribes);
	ReadConfigBool("EnableCellphone", line, cellphone);
	ReadConfigBool("EnableBriefcase", line, briefcase);
	ReadConfigBool("EnableKeycard", line, keycard);

	ReadConfigBool("MoneyInBriefcase", line, briefcaseMoney);
}
void Config::ClothesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("ClothesRandomizer", line, Enabled);
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
		CreateDirectory(Functions::GetRainbomizerDir().c_str(), NULL);

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
		clothes.Read(str);
		cutscene.Read(str);
	}
}