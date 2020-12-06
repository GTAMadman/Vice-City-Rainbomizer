#pragma once
#include "default_config.h"
#include "Functions.h"
#include <fstream>
#include <filesystem>
#include <sstream>

class Config
{
	static const std::string ConfigName;
public:
	static void Initialise();

	inline static struct General
	{
		bool replays;
		bool credits;
		void Read(const std::string& line);
	} general;

	inline static struct ScriptedVehiclesRandomizer
	{
		bool Enabled;
		bool offroadEnabled;
		bool rcEnabled;
		bool chopperCheckpointEnabled;
		bool pizzaBoyEnabled;
		void Read(const std::string& line);
	} script;

	inline static struct RCVehiclesRandomizer
	{
		bool Enabled;
		bool DriveRCVehiclesEnabled;
		void Read(const std::string& line);
	} rc;

	inline static struct ParkedVehiclesRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} parked;

	inline static struct TrafficRandomizer
	{
		bool Enabled;
		bool scriptedCopCarsEnabled;
		bool roadblocksEnabled;
		bool deadDodo;
		bool airTrain;

		bool cars;
		bool bikes;
		bool RC;
		bool boats;
		bool helis;
		bool forceVehicle;
		int forcedVehicleID = 0;
		void Read(const std::string& line);
	} traffic;

	inline static struct WeaponRandomizer
	{
		bool Enabled;
		bool RocketEnabled;
		bool tearGasEnabled;
		bool ReduceMeleeWeaponsEnabled;
		void Read(const std::string& line);
	} weapons;

	inline static struct ColourRandomizer
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

	inline static struct PickupsRandomizer
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
		bool briefcaseMoney;
		void Read(const std::string& line);
	} pickups;

	inline static struct ClothesRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} clothes;

	inline static struct VoiceLineRandomizer
	{
		bool Enabled;
		bool MatchSubtitles;
		bool loopEnabled;
		void Read(const std::string& line);
	} voice;

	inline static struct Autosave
	{
		int slot = 8;
		bool Enabled;
		void Read(const std::string& line);
	} autosave;

	inline static struct CutsceneRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} cutscene;

	static void WriteConfig();
};