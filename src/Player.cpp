#include "Player.h"

std::vector <std::string>Player::player_outfits =
{
   "PLAYER", "PLAYER2", "PLAYER3", "PLAYER4", "PLAYER5",
   "PLAYER6", "PLAYER7", "PLAYER8", "PLAYER9","PLAY11", 
   "PLAY12", "PLAY10"
};
std::vector<std::string> Player::special_models = 
{  "sam", "s_keep", "bgb", "stripc", "stripa", "stripb",
   "bga",     "burger",  "sgoona",  "sgoonb", "igken", 
   "cgona",   "dgoona",  "dgoonb", "igmerc2", "bounca",
   "floozyb", "chef", "igbuddy", "spandxa", "spandxb", 
   "iggonz", "cgonb",   "fsfa",    "courier", "igdiaz",
   "igcolon", "dgoonc","sgc",     "igmike",  "shootra", 
   "shootrb", "igphil", "ighlary", "igphil3", "igmike2", 
   "ighlry2", "igphil2", "cmraman", "mporna", "igcandy", 
   "igmerc", "crewa", "crewb","igalscb", "igbudy2", 
   "floozya", "cdrivra", "cdrivrb", "printra", "printrb", 
   "printrc", "mba", "mbb", "igsonny",  "mgoona", "mserver",
   "floozyc", "psycho", "igjezz", "igdick", "igpercy" };

std::vector<std::string> Player::all_outfits;
void __fastcall Player::RandomizeOutfit(CPed* ped, void* edx, const char* modelName)
{
	std::string newModel = all_outfits[RandomNumber(0, all_outfits.size() - 1)];

	ped->Undress(newModel.c_str());
	CStreaming::LoadAllRequestedModels(0);
	strcpy(CModelInfo::GetModelInfo(0)->m_szName, modelName);
}
void Player::GivePlayerRandomOutfit()
{
	std::string newModel = all_outfits[RandomNumber(0, all_outfits.size() - 1)];

	ChangePlayerModel(newModel.c_str());
	CStreaming::LoadAllRequestedModels(0);
	strcpy(CModelInfo::GetModelInfo(0)->m_szName, player_outfits[RandomNumber(0, 
		player_outfits.size() - 1)].c_str());
}
void __fastcall Player::FixTwoBitHit(CRunningScript* script, void* edx, char flag)
{
	if (script->m_szName == std::string("serg2") && !flag)
	{
		script->UpdateCompareFlag(1);
		return;
	}
	script->UpdateCompareFlag(flag);
}
void Player::RandomizeOutfitOnFade()
{
	static int prevFadeValue = -1;
	int fadeValue = injector::ReadMemory<uint8_t>(0xA10B16);

	if (prevFadeValue != fadeValue && fadeValue == 255)
	{
		if (FindPlayerPed())
			GivePlayerRandomOutfit();
	}
	prevFadeValue = fadeValue;
	plugin::Call<0x4A7060>();
}
void Player::ChangePlayerModel(const char* modelName)
{
	plugin::Call<0x4AE8C0>(modelName);
}
void Player::Initialise()
{
	if (Config::player.Enabled)
	{
		if (Config::player.playerOutfits)
		{
			for (std::string item : player_outfits)
			{
				all_outfits.push_back(item);
			}
		}
		if (Config::player.specialModels)
		{
			for (std::string item : special_models)
			{
				all_outfits.push_back(item);
			}
		}
		if (all_outfits.size() == 0)
			return;

		for (int addr : {0x42BDDC, 0x42C1C7, 0x42C3C9, 0x45D35A})
			plugin::patch::RedirectCall(addr, RandomizeOutfit);

		plugin::patch::RedirectCall(0x6320BC, FixTwoBitHit);

		if (Config::player.randomizeOnFades)
			plugin::patch::RedirectCall(0x4A6133, RandomizeOutfitOnFade);
	}
}