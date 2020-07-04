#include "plugin.h"
#include "Config.h"
#include "scm.h"
#include "Remote.h"
#include "Parked.h"
#include "Traffic.h"
#include "Weapons.h"
#include "Colours.h"
#include "voices.h"
#include "Pickups.h"
#include "Clothes.h"
#include "Autosave.h"

class Rainbomizer {
public:
	Rainbomizer() {
		Config::Initialise();
		scm::Initialise();
		Remote::Initialise();
		Parked::Initialise();
		Traffic::Initialise();
		Weapons::Initialise();
		Colours::Initialise();
		voices::Initialise();
		Pickups::Initialise();
		Clothes::Initialise();
		Autosave::Initialise();
	}
} rainbomizer;