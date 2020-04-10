#include "Config.h"

std::string Config::ConfigName = "Rainbomizer.cfg";

/* Annoyingly messy initialisers */
bool Config::ScriptedVehiclesRandomizer::Enabled;
bool Config::ParkedVehiclesRandomizer::Enabled;
bool Config::RCVehiclesRandomizer::Enabled;
bool Config::RCVehiclesRandomizer::DriveRCVehiclesEnabled;
bool Config::TrafficRandomizer::Enabled;
bool Config::WeaponRandomizer::Enabled;
bool Config::ColourRandomizer::vehicleEnabled;
bool Config::ColourRandomizer::textEnabled;
bool Config::ColourRandomizer::vibrantOnlyEnabled;
bool Config::ColourRandomizer::rainbowTextEnabled;
bool Config::ColourRandomizer::markersEnabled;
bool Config::VoiceLineRandomizer::Enabled;
bool Config::VoiceLineRandomizer::loopEnabled;
bool Config::Autosave::Enabled;
int Config::Autosave::slot;

/* Probably not the best way to read from and write to the config, but it works for now */
void Config::ScriptedVehiclesRandomizer::Read()
{
	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	std::vector<std::string> data;
	std::string str;
	while (std::getline(config, str))
		data.push_back(str);

	config.close();

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->Name) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->Enabled = true;
				break;
			}
			this->Enabled = false;
			break;
		}
	}
}
void Config::RCVehiclesRandomizer::Read()
{
	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	std::vector<std::string> data;
	std::string str;
	while (std::getline(config, str))
		data.push_back(str);

	config.close();

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->Name) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->Enabled = true;
				break;
			}
			this->Enabled = false;
			break;
		}
	}
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->DriveRCVehiclesName) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->DriveRCVehiclesEnabled = true;
				break;
			}
			this->DriveRCVehiclesEnabled = false;
			break;
		}
	}
}
void Config::ParkedVehiclesRandomizer::Read()
{
	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	std::vector<std::string> data;
	std::string str;
	while (std::getline(config, str))
		data.push_back(str);

	config.close();

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->Name) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->Enabled = true;
				break;
			}
			this->Enabled = false;
			break;
		}
	}
}
void Config::ColourRandomizer::Read()
{
	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	std::vector<std::string> data;
	std::string str;
	while (std::getline(config, str))
		data.push_back(str);

	config.close();

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->vehicleName) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->vehicleEnabled = true;
				break;
			}
			this->vehicleEnabled = false;
			break;
		}
	}
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->textName) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->textEnabled = true;
				break;
			}
			this->textEnabled = false;
			break;
		}
	}
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->vibrantOnlyName) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->vibrantOnlyEnabled = true;
				break;
			}
			this->vibrantOnlyEnabled = false;
			break;
		}
	}
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->rainbowTextName) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->rainbowTextEnabled = true;
				break;
			}
			this->rainbowTextEnabled = false;
			break;
		}
	}
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->markersText) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->markersEnabled = true;
				break;
			}
			this->markersEnabled = false;
			break;
		}
	}
}
void Config::TrafficRandomizer::Read()
{
	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	std::vector<std::string> data;
	std::string str;
	while (std::getline(config, str))
		data.push_back(str);

	config.close();

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->Name) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->Enabled = true;
				break;
			}
			this->Enabled = false;
			break;
		}
	}
}
void Config::WeaponRandomizer::Read()
{
	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	std::vector<std::string> data;
	std::string str;
	while (std::getline(config, str))
		data.push_back(str);

	config.close();

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->Name) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->Enabled = true;
				break;
			}
			this->Enabled = false;
			break;
		}
	}
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->WeightedWeaponRandomizationEnabledName) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->WeightedWeaponRandomizationEnabled = true;
				break;
			}
			this->WeightedWeaponRandomizationEnabled = false;
			break;
		}
	}
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->RemoteGrenadeEnabledName) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->RemoteGrenadeEnabled = true;
				break;
			}
			this->RemoteGrenadeEnabled = false;
			break;
		}
	}
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->RocketEnabledName) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->RocketEnabled = true;
				break;
			}
			this->RocketEnabled = false;
			break;
		}
	}
}
void Config::VoiceLineRandomizer::Read()
{
	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	std::vector<std::string> data;
	std::string str;
	while (std::getline(config, str))
		data.push_back(str);

	config.close();

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->Name) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->Enabled = true;
				break;
			}
			this->Enabled = false;
			break;
		}
	}
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->loopName) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->loopEnabled = true;
				break;
			}
			this->loopEnabled = false;
			break;
		}
	}
}
void Config::Autosave::Read()
{
	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	std::vector<std::string> data;
	std::string str;
	while (std::getline(config, str))
		data.push_back(str);

	config.close();

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->autosaveName) != std::string::npos)
		{
			if (data[i].find("true") != std::string::npos)
			{
				this->Enabled = true;
				break;
			}
			this->Enabled = false;
			break;
		}
	}
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find(this->slotName) != std::string::npos)
		{
			for (int x = 1; x < 9; x++)
			{
				if (data[i].find(std::to_string(x)) != std::string::npos)
				{
					this->slot = x;
					break;
				}
			}
		}
	}
	if (this->slot < 1 || this->slot > 8)
		this->slot = 8;
}
void Config::WriteConfig()
{
	std::ofstream config;
	config.open(ConfigName);

	for (int i = 0; i < sizeof(default_config); i++)
	{
		config << (char)default_config[i];
	}
	config.close();
}
void Config::Initialise()
{
	ScriptedVehiclesRandomizer script;
	script.Read();

	RCVehiclesRandomizer rc;
	rc.Read();

	ParkedVehiclesRandomizer parked;
	parked.Read();

	TrafficRandomizer traffic;
	traffic.Read();

	WeaponRandomizer weapons;
	weapons.Read();

	ColourRandomizer colours;
	colours.Read();

	Autosave autosave;
	autosave.Read();

	VoiceLineRandomizer voice;
	voice.Read();
}
