#pragma once
#include "default_config.h"
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

class Config
{
public:
	static void Initialise();

	static struct ScriptedVehiclesRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} script;

	static struct RCVehiclesRandomizer
	{
		bool Enabled;
		bool DriveRCVehiclesEnabled;
		void Read(const std::string& line);
	} rc;

	static struct ParkedVehiclesRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} parked;

	static struct TrafficRandomizer
	{
		bool Enabled;
		bool scriptedCopCarsEnabled;
		bool roadblocksEnabled;
		bool deadDodo;
		bool airTrain;
		void Read(const std::string& line);
	} traffic;

	static struct WeaponRandomizer
	{
		bool Enabled;
		bool RocketEnabled;
		bool ReduceMeleeWeaponsEnabled;
		void Read(const std::string& line);
	} weapons;

	static struct ColourRandomizer
	{
		bool vehicleEnabled;
		bool textEnabled;
		bool vibrantOnlyEnabled;
		bool rainbowTextEnabled;
		bool markersEnabled;
		bool pickupsEnabled;
		bool lazerScopeEnabled;
		bool explosionsEnabled;
		void Read(const std::string& line);
	} colours;

	static struct PickupsRandomizer
	{
		bool Enabled;
		bool randomizePedDrops;
		bool weapons;
		bool health;
		bool armour;
		bool adrenaline;
		bool bribes;
		bool cellphone;
		bool briefcase;
		bool keycard;
		void Read(const std::string& line);
	} pickups;

	static struct ClothesRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} clothes;

	static struct VoiceLineRandomizer
	{
		bool Enabled;
		bool MatchSubtitles;
		bool loopEnabled;
		void Read(const std::string& line);
	} voice;

	static struct Autosave
	{
		int slot = 8;
		bool Enabled;
		void Read(const std::string& line);
	} autosave;

	static void WriteConfig();
};