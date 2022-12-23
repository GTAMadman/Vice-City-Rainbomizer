#include "plugin.h"
#include "Config.h"
#include "Script.h"
#include "Remote.h"
#include "Parked.h"
#include "Traffic.h"
#include "Weapons.h"
#include "Colours.h"
#include "Voices.h"
#include "Pickups.h"
#include "Player.h"
#include "Ped.h"
#include "Cutscenes.h"
#include "Missions.h"
#include "Credits.h"
#include "General.h"
#include "Autosave.h"

class Rainbomizer {
public:
	Rainbomizer() {
		Config::Initialise();
		General::Initialise();
		Script::Initialise();
		Remote::Initialise();
		Parked::Initialise();
		Traffic::Initialise();
		Weapons::Initialise();
		Colours::Initialise();
		Voices::Initialise();
		Pickups::Initialise();
		Player::Initialise();
		Ped::Initialise();
		Cutscenes::Initialise();
		Missions::Initialise();
		Credits::Initialise();
		Autosave::Initialise();
	}
} rainbomizer;