#include "plugin.h"
#include "Config.h"
#include "scm.h"
#include "Remote.h"
#include "Parked.h"
#include "Traffic.h"
#include "Weapons.h"
#include "Colours.h"
#include "voices.h"
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
		Autosave::Initialise();
	}
} rainbomizer;
