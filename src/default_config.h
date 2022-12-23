#pragma once
const char default_config[]
= R"(# GTA Vice City Rainbomizer Configuration #

###########################################
# General Configuration

DisableReplays = false
ModifyCredits = true
EnableEasterEggs = true

###########################################
# Script Vehicles Randomizer
ScriptVehiclesRandomizer = true

# Allow certain side missions to be activated by any vehicle

OffroadMissions = true # (Trial by Dirt (bikes only), Test Track (cars only), PCJ Playground, Cone Crazy)
RCMissions = true # (RC Raider Pickup, RC Bandit Race, RC Baron Race)
ChopperCheckpoints = true # (Will only be activated by helicopters)
PizzaBoy = true # (Activate and use any vehicle for pizza boy)

# Force a script vehicle
ForcedScriptVehicle = 0

###########################################
# RC Vehicles Randomizer
RandomizeRCVehicles = true

# Experimental - this feature may cause crashes, softlocks or possibly lag
# It is currently known that you are unable to re-enter RC vehicles once exited

AllowPlayerToDriveRCVehicles = false

###########################################
# Parked Vehicles Randomizer
ParkedVehiclesRandomizer = true

# Force a parked vehicle
ForcedParkedVehicle = 0

###########################################
# Colour Randomizer

# Vehicles
RandomizeVehicleColours = true

# HUD
RandomizeHUDColours = true
RainbowHUDColours = false

# Markers
RandomizeMarkerColours = true
StaticMarkerColours = false

# Pickups
RandomizePickupColours = true
StaticPickupColours = false

# Lazer Scope
RandomizeLazerScopeColour = true
StaticLazerScopeColours = false

# Explosions
RandomizeExplosionColours = true
StaticExplosionColours = false

###########################################
# Traffic Randomizer
TrafficRandomizer = true

# Randomizes police vehicles which intercept you on some roads
RandomizeScriptedCopCars = true

RandomizeRoadblocks = true

# Vehicle types allowed to spawn in traffic
EnableCars = true
EnableBikes = true
EnableRC = true
EnableBoats = true
EnableHelis = true

# Additional vehicles
EnableDeadDodo = true
EnableAirTrain = true

# Force a traffic vehicle
ForcedTrafficVehicle = 0

###########################################
# Weapon Randomizer
WeaponRandomizer = true

# Gives the player random weapons
RandomizePlayerWeapons = true

# Gives the player random weapons for rampages
RandomizeRampageWeapons = true

# Randomizes the weapons differently to reduce the chances of peds being given melee weapons

ReduceMeleeWeapons = false

# Allows peds to be given the missile - WARNING: When dropped this flashes heavily, may effect certain
# people with epilepsy or sensitivity - may also cause game crashes

AllowRocketMissile = false

# Tear gas can sometimes cause lag when used by peds
AllowTearGas = true

# Force a weapon
ForcedWeapon = 0

###########################################
# Pickups Randomizer

# Randomizes weapons, health, armour, adrenaline, bribe stars and mission pickups
# This feature is safe to use, though pickups are saved to the save file
 
PickupsRandomizer = true

# Randomizes the weapons dropped by dead peds
RandomizePedWeaponDrops = true

# Randomizes the weapons taken away by metal detectors
RandomizeMetalDetectorWeapons = true

# Allowed pickup types
EnableWeapons = true
EnableHealth = true
EnableArmour = true
EnableAdrenaline = true
EnableBribes = true
EnableCellphone = true
EnableBriefcase = true
EnableKeycard = true

# Randomize a small amount of money given by a briefcase pickup
MoneyInBriefcase = true

# Enter your own seed - if empty, the seed will be random
PickupsCustomSeed = ""

# Force a pickup
ForcedPickup = 0

###########################################
# Player Randomizer
PlayerRandomizer = true

RandomizePlayerOutfits = true
IncludeSpecialModels = true

RandomizeOnFades = true

# Force a player model
ForcedPlayerModel = ""

###########################################
# Ped Randomizer
PedRandomizer = true

# Randomizes special mission peds
RandomizeSpecialModels = true

# Randomizes generic peds on the streets, in vehicles and some missions
RandomizeGenericPeds = true

# Randomizes cops on the streets, in vehicles and at roadblocks
RandomizeCopPeds = true

# Special models will also be able to become player models
IncludePlayerModels = true

# Force a ped model
ForcedPedModel = -1

###########################################
# Mission Randomizer
MissionRandomizer = true

# Enter your own seed - if empty, the seed will be random
MissionCustomSeed = ""

# Force a specific mission
ForcedMission = 0

###########################################
# Cutscene Randomizer
CutsceneRandomizer = true

###########################################
# Voice Line Randomizer
VoiceLineRandomizer = true

# Matches the subtitles to the randomized voice line
MatchSubtitles = true

# Phonecall ringtones will loop the same sound over being re-randomized
LoopPhoneRingtone = true

###########################################
# Autosave
Autosave = true
Slot = 8)";