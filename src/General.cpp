#include "General.h"

char* aMainEventTonig = reinterpret_cast<char*>(0x69679C);
char* aMainEventTon_0 = reinterpret_cast<char*>(0x696800);
char* aMainEventTon_1 = reinterpret_cast<char*>(0x69686C);
char* aForTicketsToTh = reinterpret_cast<char*>(0x6967C4);
char* aForTicketsTo_1 = reinterpret_cast<char*>(0x696898);
char* aForTicketsTo_0 = reinterpret_cast<char*>(0x696830);

std::vector<std::string> credits = { "GTA MADMAN", "PARIK", "123ROBOT", "FRYTERP23", 
"ADS SAL", "HUGO ONE", "SPEEDYFOLF", "TUBEWAYARMY", "VOD CRACK" };

void General::Initialise()
{
	if (Config::general.easterEggs)
	{
		std::string hotring = "FOR TICKETS TO THE HOT RING EVENT CALL " 
			+ credits[RandomNumber(0, credits.size() - 1)] + " . . .   ";

		std::string dirtring = "FOR TICKETS TO THE DIRT RING EVENT CALL " 
			+ credits[RandomNumber(0, credits.size() - 1)] + " . . .   ";

		std::string bloodring = "FOR TICKETS TO THE BLOOD RING EVENT CALL " 
			+ credits[RandomNumber(0, credits.size() - 1)] + " . . .   ";

		memcpy(aMainEventTonig, "MAIN EVENT TONIGHT: RAINBOMIZER RACING . . .   ", 48);
		memcpy(aMainEventTon_0, "MAIN EVENT TONIGHT: RAINBOMIZER DERBY . . .   ", 47);
		memcpy(aMainEventTon_1, "MAIN EVENT TONIGHT: RAINBOMIZER RACING . . .   ", 48);

		memcpy(aForTicketsToTh, hotring.c_str(), hotring.size());
		memcpy(aForTicketsTo_1, dirtring.c_str(), dirtring.size());
		memcpy(aForTicketsTo_0, bloodring.c_str(), bloodring.size());
	}

	if (Config::general.replays)
		plugin::patch::Nop(0x4A45C3, 5);
}