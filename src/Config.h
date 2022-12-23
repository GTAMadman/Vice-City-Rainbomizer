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
		bool easterEggs;
		void Read(const std::string& line);
	} general;

	inline static struct ScriptedVehiclesRandomizer
	{
		bool Enabled;
		bool offroadEnabled;
		bool rcEnabled;
		bool chopperCheckpointEnabled;
		bool pizzaBoyEnabled;
		int forcedVehicle = 0;
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
		int forcedVehicle = 0;
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
		int forcedVehicle = 0;
		void Read(const std::string& line);
	} traffic;

	inline static struct WeaponRandomizer
	{
		bool Enabled;
		bool randomizePlayerWeapons;
		bool randomizeRampageWeapons;
		bool RocketEnabled;
		bool tearGasEnabled;
		bool ReduceMeleeWeaponsEnabled;
		int forcedWeapon = 0;
		void Read(const std::string& line);
	} weapons;

	inline static struct ColourRandomizer
	{
		bool vehicleEnabled;
		bool textEnabled;
		bool rainbowTextEnabled;
		bool markersEnabled;
		bool pickupsEnabled;
		bool lazerScopeEnabled;
		bool explosionsEnabled;
		bool staticMarkerColours;
		bool staticPickupColours;
		bool staticLazerScopeColours;
		bool staticExplosionColours;
		void Read(const std::string& line);
	} colours;

	inline static struct PickupsRandomizer
	{
		bool Enabled;
		bool randomizePedDrops;
		bool randomizeMetalDetectorWeps;
		bool weapons;
		bool health;
		bool armour;
		bool adrenaline;
		bool bribes;
		bool cellphone;
		bool briefcase;
		bool keycard;
		bool briefcaseMoney;
		std::string seed;
		bool usingSeed;
		int forcedPickup = 0;
		void Read(const std::string& line);
	} pickups;

	inline static struct PlayerRandomizer
	{
		bool Enabled;
		bool playerOutfits;
		bool specialModels;
		bool randomizeOnFades;
		std::string forcedModel = "";
		void Read(const std::string& line);
	} player;

	inline static struct PedRandomizer
	{
		bool Enabled;
		bool specialModels;
		bool genericPeds;
		bool copPeds;
		bool playerModels;
		int forcedPed = 0;
		void Read(const std::string& line);
	} ped;

	inline static struct MissionRandomizer
	{
		bool Enabled;
		bool usingSeed;
		std::string seed;
		int forcedMission;
		void Read(const std::string& line);
	} mission;

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