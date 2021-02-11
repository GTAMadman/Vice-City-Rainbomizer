Rainbomizer is a randomizer for Grand Theft Auto Vice City.

<img src="https://cdn.discordapp.com/attachments/651869008618061837/678350944890781739/r1outink.png">
Logo created by Catmare

## Features

- **Script Vehicle Randomizer**: Randomizes the vehicles you are given in missions. The randomizer makes sure that you get vehicles that are usable for the mission.
- **RC Vehicles Randomizer**: Randomizes the vehicles you are given in the RC missions.
- **Parked Vehicles Randomizer**: Randomizes cars which are found parked around the map.
- **Colour Randomizer**: Randomizes the colours of various in-game elements, including cars, the HUD, markers, pickups, explosions and more!
- **Traffic Randomizer**: Randomizes vehicles that spawn in traffic, including law enforcement vehicles.
- **Weapon Randomizer**: Randomizes the weapons that are given to other peds throughout the game.
- **Pickups Randomizer**: Randomizes pickups throughout the world, including pickups given to you by missions and dropped by peds.
- **Voice Line Randomizer**: Randomizes the voice lines played in missions and phonecalls.
- **Cutscene Randomizer**: Randomizes the models used in motion-captured cutscenes.
- **Mission Randomizer**: Randomizes which mission is started by each mission marker. When the randomized mission is complete, the game progresses as if you completed the original.
- **Player Randomizer**: Randomizes the player outfit between the player and special models on fades.
- **Ped Randomizer**: Randomizes generic peds, police peds and mission peds.
- **Autosave**: Automatically creates a savegame in slot 8 upon completing a mission. The autosave slot can be changed in the config file.

## Supported Versions

* GTA Vice City - v1.0

Other versions of the game *will not* work and will most likely cause a crash.

Check this link for a v1.0 EXE - https://cdn.discordapp.com/attachments/681997098153148433/682719019052040229/gta-vc.exe

## Configuration

If you wish to change any of the mod's functionalities, for example to disable a specific randomizer, a configuration file (`config.cfg`) has been provided with the mod. The config file is located in the ('rainbomizer') folder in the game's root directory.

The default configuration file is in the main repository, `config.cfg`, and is automatically created by the mod if it doesn't exist in the game folder.

The configuration file is in the CFG format.

To configure a specific randomizer, search for its name in the configuration file. You can set it to 'true' or 'false' to enable or disable it respectively.

Configuration options marked with '# Experimental' are not fully complete and will still have issues.

More information about how to configure specific randomizers is provided in the default config file.

## Installation

1) Downgrade to 1.0 (download link available above)
2) Download the latest version from the releases page: https://github.com/GTAMadman/Vice-City-Rainbomizer/releases
3) Put the ASI file and ('rainbomizer') folder into your GTA Vice City directory.

- It is recommended to not use CLEO with this mod as it can prevent the autosave function from working properly.
- It is recommended to run the game with one core affinity to prevent game freezes (Vice City issue).

## Credits

#### Lead Developers

- [GTA Madman](https://github.com/gta_madman) - Creation and implementation of the ASI.
- [Parik27](https://github.com/parik27) - Helping with function hooks and suggestions.

### Contributors
- [123robot](https://www.twitch.tv/123robot) - Testing and helping with parts of the mod
- [Fryterp23](https://www.twitch.tv/fryterp23) - Extensive testing of the mod

#### Original Concept

- [NABN00B](https://www.twitch.tv/nabn00b) - Gave the original idea for a car randomizer for San Andreas.
- [MrMateczko](https://www.twitch.tv/mrmateczko_) - Special mention for sharing a modded cargrp file for San Andreas that led to the original idea.
- [Veigar](https://gtaforums.com/profile/685882-veigar) - Idea for the Parked Car randomizer for San Andreas.

#### Beta Testers

- [Hugo_One](https://www.twitch.tv/hugo_one) - Streaming the mod
- [Vod_Crack](https://www.twitch.tv/vod_crack) - Testing and streaming of the mod
- [SpeedyFolf](https://www.twitch.tv/speedyfolf) - Testing and streaming the mod
= [TubewayArmy](https://www.speedrun.com/user/TubewayArmy) - Testing and streaming the mod
- [Ads_Sal](https://www.twitch.tv/ads_sal) - Testing the mod

## Used Libraries

- [plugin-sdk](https://github.com/DK22Pac/plugin-sdk)

## Contribution

You can contribute to the project by reporting any crashes/issues you encounter in the [Issues](https://github.com/GTAMadman/Vice-City-Rainbomizer/issues) section of the repository.

Pull requests are welcome, but are required to follow the current style used in the project.

You can also keep up with or contribute to development as it happens by [joining the official Rainbomizer Discord](https://discord.gg/BYVBQw7)
