#pragma once
const char default_config[]
= R"(
# GTA Vice City Rainbomizer Configuration #

###########################################
# Script Vehicles Randomizer
ScriptVehiclesRandomizer = true

###########################################
# RC Vehicles Randomizer
RandomizeRCVehicles = true

# Experimental - this feature may cause crashes, softlocks or possibly lag
# It is currently known that you are unable to re-enter RC vehicles once exited

AllowPlayerToDriveRCVehicles = false

###########################################
# Parked Vehicles Randomizer
ParkedVehiclesRandomizer = true

###########################################
# Colour Randomizer
RandomizeVehicleColours = true
RandomizeTextColours = true
RandomizeMarkerColours = true

# If both below are false with text colours enabled, they will be normal random colours

RainbowTextColours = false
VibrantStaticTextColoursOnly = false

###########################################
# Traffic Randomizer
TrafficRandomizer = true

###########################################
# Weapon Randomizer
WeaponRandomizer = true

# Randomizes the weapons differently to reduce the chances of peds being given melee weapons

ReduceMeleeWeapons = false

# Allows peds to be given the missile - WARNING: When dropped this flashes heavily, may effect certain
# people with epilepsy or sensitivity

AllowRocketMissile = false

###########################################
# Voice Line Randomizer

# Experimental - subtitles do not match randomized audio
VoiceLineRandomizer = false

# Phonecall ringtones will loop the same sound over being re-randomized
LoopPhoneRingtone = true

###########################################
# Autosave
Autosave = true
Slot = 8
)";
