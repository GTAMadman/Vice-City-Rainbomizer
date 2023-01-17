#include "Player.h"

std::vector <std::string> Player::player_outfits =
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

auto GetAnimBlendClumpData(RpClump* clump)
{
	return *((CAnimBlendClumpData **)(((uint8_t*)clump) + injector::ReadMemory<uint32_t>(0x978798)));
}

auto RpAnimBlendClumpExtractAssociations(RpClump* clump)
{
	auto data = GetAnimBlendClumpData(clump);

	auto ret = data->m_associationsList.link.next;
	data->m_associationsList.link.next = nullptr;
	ret->prev = nullptr;

	return (CAnimBlendAssociation*)ret;
}
auto RpAnimBlendClumpGiveAssociations(RpClump* clump, CAnimBlendAssociation* association) 
{
	if (!association)
		return;

	auto data = GetAnimBlendClumpData(clump);
	auto assoc = &data->m_associationsList.link;
	auto baseAssoc = &data->m_associationsList.link;

	while (assoc->next)
	{
		auto next = assoc->next;
		((CAnimBlendAssociation*)(((uint8_t*)assoc->next) - 4))->~CAnimBlendAssociation();
		assoc = next;
	}

	baseAssoc->next = (RwLLLink*)association;
	((RwLLLink*)association)->prev = baseAssoc;
}
void __fastcall Player::RandomizeOutfit(CPed* ped, void* edx, const char* modelName) 
{
	std::string newModel = all_outfits[RandomNumber(0, all_outfits.size() - 1)];

	if (Config::player.forcedModel != "")
		newModel = Config::player.forcedModel;

	association = RpAnimBlendClumpExtractAssociations(ped->m_pRwClump);

	ped->Undress(newModel.c_str());
	CStreaming::LoadAllRequestedModels(0);
	strcpy(CModelInfo::GetModelInfo(0)->m_szName, modelName);
}
void __fastcall Player::FixAnimAfterModelChange(CPed* ped)
{
	ped->Dress();
	if (association)
	{
		RpAnimBlendClumpGiveAssociations(ped->m_pRwClump, association);
		association = nullptr;
	}
}
void Player::GivePlayerRandomOutfit()
{
	std::string newModel = all_outfits[RandomNumber(0, all_outfits.size() - 1)];

	if (Config::player.forcedModel != "")
		newModel = Config::player.forcedModel;

	CPed* ped = FindPlayerPed();
	association = RpAnimBlendClumpExtractAssociations(ped->m_pRwClump);

	ChangePlayerModel(newModel.c_str());
	CStreaming::LoadAllRequestedModels(0);
	strcpy(CModelInfo::GetModelInfo(0)->m_szName, player_outfits[RandomNumber(0,
		player_outfits.size() - 1)].c_str());

	RpAnimBlendClumpGiveAssociations(ped->m_pRwClump, association);
	association = nullptr;
}
void __fastcall Player::FixTwoBitHit(CRunningScript* script, void* edx, char flag)
{
	if (IsMission("serg2") && !flag)
		flag = 1;
	script->UpdateCompareFlag(flag);
}
void __fastcall Player::FixPlayerPositionAtStartOfMissions(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);

	float& posZ = CTheScripts::ScriptParams[3].fParam;
	if (IsMission("protec1") || IsMission("protec2") && posZ == 16.2f)
		posZ = 17.2f;
	if (IsMission("protec3") && posZ == 11.7f)
		posZ = 12.7f;
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
				all_outfits.push_back(item);
		}
		if (Config::player.specialModels)
		{
			for (std::string item : special_models)
				all_outfits.push_back(item);
		}
		if (all_outfits.size() == 0)
			return;

		for (int addr : {0x42BDDC, 0x42C1C7, 0x42C3C9, 0x45D35A})
			plugin::patch::RedirectCall(addr, RandomizeOutfit);

		for (int addr : {0x42BE00, 0x42C1EB, 0x42C3ED, 0x45D3A0})
			plugin::patch::RedirectCall(addr, FixAnimAfterModelChange);

		plugin::patch::RedirectCall(0x6320BC, FixTwoBitHit);
		plugin::patch::RedirectCall(0x44EA27, FixPlayerPositionAtStartOfMissions);

		if (Config::player.randomizeOnFades)
			plugin::patch::RedirectCall(0x4A6133, RandomizeOutfitOnFade);
	}
}