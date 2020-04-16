#include "Config.h"
#include <fstream>
#include <filesystem>
#include <vector>

const std::string ConfigName = "Rainbomizer.cfg";

/* Annoyingly messy initialisers */
Config::ScriptedVehiclesRandomizer Config::script;
Config::RCVehiclesRandomizer Config::rc;
Config::TrafficRandomizer Config::traffic;
Config::WeaponRandomizer Config::weapons;
Config::ColourRandomizer Config::colours;
Config::VoiceLineRandomizer Config::voice;
Config::Autosave Config::autosave;

void ReadConfigBool(const std::string &key, const std::string &data, bool &value)
{
	if(data[i].find(key) != std::string::npos)
		value = data[i].find("true") != std::string::npos;
}

template<typename F>
void ReadConfigCustom(const std::string &key, const std::string &data, F &pred)
{
	if(data[i].find(key) != std::string::npos)
		pred();
}

/* Probably not the best way to read from and write to the config, but it works for now */
void Config::ScriptedVehiclesRandomizer::Read(const std::string &line)
{
	ReadConfigBool("ScriptVehiclesRandomizer", line, Enabled);
}
void Config::RCVehiclesRandomizer::Read(const std::string &line)
{
	ReadConfigBool("RandomizeRCVehicles", line, Enabled);
}
void Config::ParkedVehiclesRandomizer::Read(const std::string &line)
{
	ReadConfigBool("ParkedVehiclesRandomizer", line, Enabled);
}
void Config::ColourRandomizer::Read(const std::string &line)
{
	ReadConfigBool("RandomizeVehicleColours", line, vehicleEnabled);
	ReadConfigBool("RandomizeTextColours", line, textEnabled);
	ReadConfigBool("RandomizeMarkerColours", line, markersEnabled);
	ReadConfigBool("RainbowTextColours", line, rainbowTextEnabled);
	ReadConfigBool("VibrantStaticTextColoursOnly", line, vibrantOnlyEnabled);
}
void Config::TrafficRandomizer::Read(const std::string &line)
{
	ReadConfigBool("TrafficRandomizer", line, Enabled);
}
void Config::WeaponRandomizer::Read(const std::string &line)
{
	ReadConfigBool("WeaponRandomizer", line, Enabled);
}
void Config::VoiceLineRandomizer::Read(const std::string &line)
{
	ReadConfigBool("VoiceLineRandomizer", line, Enabled);
	ReadConfigBool("LoopPhoneRington", line, loopEnabled);
}
void Config::Autosave::Read(const std::string &line)
{
	ReadConfigBool("Autosave", line, Enabled);
	ReadConfigCustom("Slot", line, [this] {
		for (int x = 1; x < 9; x++)
			{
				if (data[i].find(std::to_string(x)) != std::string::npos)
				{
					this->slot = x;
					break;
				}
			}
	});
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
	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	for(std::string str; std::getline(config, str); )
		{
			script.Read(str);
			rc.Read(str);
			parked.Read(str);
			traffic.Read(str);
			weapons.Read(str);
			colours.Read(str);
			autosave.Read(str);
			voice.Read(str);
		}
}
