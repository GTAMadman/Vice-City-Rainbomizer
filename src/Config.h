#pragma once
#include "default_config.h"
#include <string>

class Config
{
public:
	static void Initialise();

	static struct ScriptedVehiclesRandomizer
	{
		bool Enabled;
		void Read(const std::string &line);
	} script;

	static struct RCVehiclesRandomizer
	{
		bool Enabled;
		bool DriveRCVehiclesEnabled;
		void Read(const std::string &line);
	} rc;

	struct ParkedVehiclesRandomizer
	{
		bool Enabled;
		void Read(const std::string &line);
	} parked;

	static struct TrafficRandomizer
	{
		bool Enabled;
		void Read(const std::string &line);
	} traffic;

	static struct WeaponRandomizer
	{
		bool Enabled;
		void Read(const std::string &line);
	} weapons;

	static struct ColourRandomizer
	{
		bool vehicleEnabled;
		bool textEnabled;
		bool vibrantOnlyEnabled;
		bool rainbowTextEnabled;
		bool markersEnabled;
		void Read(const std::string &line);
	} colours;

	static struct VoiceLineRandomizer
	{
		bool Enabled;
		bool loopEnabled;
		void Read(const std::string &line);
	} voice;

	static struct Autosave
	{
		int slot = 8;
		bool Enabled;
		void Read(const std::string &line);
	} autosave;
	
	static void WriteConfig();
};
