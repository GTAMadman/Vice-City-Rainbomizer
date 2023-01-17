#include"Voices.h"
#include <map>

struct MissionAudioData
{
	char* SoundName;
	uint32_t SoundId;
};
std::unordered_map<std::string, std::string> subtitles{ {
	{"mob_52a", "mob52_a"}, {"mob_52b", "mob52_b"}, {"mob_52c", "mob52_c"},
	{"mob_52d", "mob52_d"}, {"mob_52e", "mob52_e"}, {"mob_52f", "mob52_f"},
	{"mob_52g", "mob52_g"}, {"mob_52h", "mob52_h"}, {"mob_71a", "mob21_a"},
	{"mob_71b", "mob21_b"}, {"mob_71c", "mob21_g"}, {"mob_71d", "mob21_h"},
	{"mob_71e", "mob21_i"}, {"mob_71f", "mob21_k"}, {"mob_71g", "mob21_m"},
	{"mob_71h", "mob21_n"}, {"mob_71i", "mob21_o"}, {"mob_71j", "mob21_p"},
	{"mob_71k", "mob21_q"}, {"mob_71l", "mob21_r"}, {"mob_71m", "mob21_t"},
	{"mob_71n", "mob21_u"}, {"mob_46a", "mob46_a"}, {"mob_46b", "mob46_b"},
	{"mob_46c", "mob46_c"}, {"mob_46d", "mob46_d"}, {"mob_46e", "mob46_e"},
	{"mob_46f", "mob46_f"}, {"mob_46g", "mob46_g"}, {"mob_46h", "mob46_h"},
	{"mob_45a", "mob45_a"}, {"mob_45b", "mob45_b"}, {"mob_45c", "mob45_c"},
	{"mob_45d", "mob45_d"}, {"mob_45e", "mob45_e"}, {"mob_45f", "mob45_f"},
	{"mob_45g", "mob45_g"}, {"mob_45h", "mob45_h"}, {"mob_45i", "mob45_i"},
	{"mob_45j", "mob45_j"}, {"mob_45k", "mob45_k"}, {"mob_45l", "mob45_l"},
	{"mob_45m", "mob45_m"}, {"mob_45n", "mob45_n"}, {"mob_17e", "mob_17f"},
	{"law1_7", "law1_12"},  {"law1_8", "law1_13"},  {"law1_1", "law1_5"},
	{"law1_2", "law1_6"},   {"law1_3", "law1_7"},   {"law1_4", "law1_9"},
	{"law1_5", "law1_10"},  {"law1_6", "law1_11"},  {"law1_9", "law1_14"},
	{"law1_10", "law1_15"}, {"lanamu1", "law2_16"}, {"lanamu2", "law2_17"},
	{"law2_6", "law2_14"},  {"law2_7", "lance_1"},  {"law2_8", "lance_2"},
	{"law2_9", "lance_3"},  {"law2_10", "lance_4"}, {"law3_20", "law3_21"},
	{"law3_14", "law3_23"}, {"law3_16", "law3_22"}, {"law3_24", "law3_16"},
	{"law3_25", "law3_17"}, {"law4_1a", "law4_1"},  {"law4_1b", "law4_2"},
	{"law4_1c", "law4_3"},  {"law4_1d", "law4_4"},  {"law4_10", "law4_5"},
	{"law4_8", "law4_10"},  {"law4_4", "law4_7"},   {"law4_9", "law4_15"},
	{"law4_6", "law4_9"},   {"law4_3", "law4_6"},   {"law4_5", "law4_11"},
	{"law4_7", "law4_12"},  {"ass_1", "ass1_1"},    {"ass_2", "ass1_2"},
	{"ass_3", "ass1_3"},    {"ass_4", "ass1_4"},    {"ass_5", "ass1_5"},
	{"ass_6", "ass1_6"},    {"ass_7", "ass1_7"},    {"ass_8", "ass1_8"},
	{"ass_9", "ass1_9"},    {"ass_10", "ass1_10"},  {"ass_11", "ass1_11"},
	{"ass_12", "ass1_12"},  {"ass_13", "ass1_13"},  {"ass_14", "ass1_14"},
	{"bk4_14b", "bk4_14a"}, {"bk4_23b", "bk4_23a"}, {"bk4_31b", "bk4_31a"},
	{"bk4_40b", "bk4_40a"}, {"bnk2_9", "bnk2_9a"},  {"bnk3_4a", "bjm3_2a"},
	{"bnk3_4b", "bjm3_2d"}, {"bnk3_4c", "bjm3_2e"}, {"bnk4_39", "bnk_39"},
	{"bnk4_41", "bk4_35b"}, {"bnk4_99", "bnk4_36"}, {"bnk422b", "bnk422a"},
	{"bud1_1", "pro1_04"},  {"bud1_2", "pro1_05"},  {"bud1_3", "pro1_06"},
	{"bud1_4", "pro1_07"},  {"bud1_5", "pro1_08"},  {"bud1_9", "pro1_09"},
	{"bud1_10", "pro1_10"}, {"bud2_1", "pro2_11"},  {"bud2_2", "pro2_02"},
	{"bud2_3", "pro2_03"},  {"bud2_4", "pro2_04"},  {"bud2_5", "pro2_05"},
	{"bud2_6", "pro2_06"},  {"bud2_7", "pro2_07"},  {"bud3_1", "pro3_09"},
	{"bud3_1a", "pro3_01"}, {"bud3_1b", "pro3_19"}, {"bud3_1c", "pro3_13"},
	{"bud3_2", "pro3_10"},  {"bud3_3", "pro3_11"},  {"bud3_4", "pro3_12"},
	{"bud3_5", "pro3_14"},  {"bud3_6", "pro3_15"},  {"bud3_7", "pro3_16"},
	{"bud3_8a", "pro3_17"}, {"bud3_9a", "pro3_18"}, {"cok2_7a", "cok2_7"},
	{"cok2_7b", "cok2_8"},  {"cok2_7c", "cok2_9"},  {"cok2_8a", "cok2_10"},
	{"cok2_8b", "cok2_11"}, {"cok2_8c", "cok2_12"}, {"cok2_8d", "cok2_13"},
	{"cok2_9", "cok2_14"},  {"cok2_13", "cok2_20"}, {"cok2_14", "cok2_21"},
	{"cok2_15", "cok2_22"}, {"cok2_16", "cok2_23"}, {"cok2_20", "cok2_27"},
	{"cok2_21", "cok2_28"}, {"cok210a", "cok2_15"}, {"cok210b", "cok2_16"},
	{"cok210c", "cok2_17"}, {"cok212a", "cok2_18"}, {"cok212b", "cok2_19"},
	{"col1_1", "gen1_06"},  {"col1_2", "gen1_07"},  {"col1_3", "gen1_08"},
	{"col1_4", "gen1_09"},  {"col1_5", "gen1_10"},  {"col1_6", "gen1_11"},
	{"col1_7", "gen1_12"},  {"col1_8", "gen1_13"},  {"col3_1", "gen3_1"},
	{"col3_2", "gen3_2"},   {"col3_2a", "gen3_3"},  {"col3_2b", "gen3_4"},
	{"col3_3", "gen3_5"},   {"col3_4", "gen3_6"},   {"col3_5", "gen3_7"},
	{"col3_6", "gen3_8"},   {"col3_7", "gen3_13"},  {"col3_8", "gen3_14"},
	{"col3_9", "gen3_15"},  {"col3_10", "gen3_16"}, {"col3_11", "gen3_17"},
	{"col3_12", "gen3_9"},  {"col3_13", "gen3_10"}, {"col3_14", "gen3_11"},
	{"col3_15", "gen3_12"}, {"col3_17", "gen3_47"}, {"col3_18", "gen3_46"},
	{"col3_19", "gen3_48"}, {"col3_20", "gen3_48"}, {"col3_21", "gen3_55"},
	{"col3_23", "gen3_52"}, {"col3_24", "gen3_53"}, {"col3_25", "gen3_54"},
	{"cub1_1", "cub1_03"},  {"cub1_2", "cub1_04"},  {"cub1_3", "cub1_05"},
	{"cub1_4", "cub1_06"},  {"cub1_5", "cub1_07"},  {"cub1_6", "cub1_08"},
	{"cub1_7", "cub1_09"},  {"cub1_8", "cub1_10"},  {"cub1_9", "cub1_01"},
	{"cub1_10", "cub1_02"}, {"cub2_1", "cub2_01"},  {"cub2_2", "cub2_19"},
	{"cub2_3a", "cub2_12"}, {"cub2_3b", "cub2_13"}, {"cub2_3c", "cub2_14"},
	{"cub2_4a", "cub2_21"}, {"cub2_5", "cub2_09"},  {"cub2_6", "cub2_07"},
	{"cub2_7", "cub2_02"},  {"cub2_8", "cub2_05"},  {"cub2_9", "cub2_15"},
	{"cub2_10", "cub2_16"}, {"cub2_11", "cub2_17"}, {"cub3_1", "cub3_08"},
	{"cub3_2", "cub3_01"},  {"cub3_3", "cub3_05"},  {"cub3_4", "cub3_06"},
	{"cub4_1", "cub4_07"},  {"cub4_2", "cub4_08"},  {"cub4_3", "cub4_09"},
	{"cub4_4", "cub4_10"},  {"cub4_5", "cub4_11"},  {"cub4_5a", "cub4_12"},
	{"cub4_6", "cub4_13"},  {"cub4_7", "cub4_14"},  {"cub4_8", "cub4_15"},
	{"cub4_9", "cub4_16"},  {"cub4_10", "cub4_17"}, {"cub4_11", "cub4_18"},
	{"cub4_12", "cub4_19"}, {"cub4_13", "cub4_20"}, {"cub4_14", "cub4_21"},
	{"cub4_15", "cub4_22"}, {"cub4_16", "cub4_23"}, {"mob_03d", "mob_03f"},
	{"mob_03e", "mob_03d"}, {"job1_1b", "asm1_d"},  {"job1_1c", "asm1_c"},
	{"job1_1d", "asm1_b"},  {"job2_1b", "asm2_a"},  {"job2_2", "asm2_13"},
	{"job2_3", "asm2_13"},  {"job2_4", "asm2_11"},  {"job2_5", "asm2_13"},
	{"job2_6", "asm2_13"},  {"job2_7", "asm2_12"},  {"job2_8", "asm2_13"},
	{"job2_9", "asm2_13"},  {"job3_1", "asm3_c"},   {"job3_2", "asm3_d"},
	{"job3_3", "asm3_e"},   {"job4_1", "asm4_a"},   {"job4_2", "asm4_b"},
	{"job4_3", "asm4_c"},   {"job5_1", "asm5_a"},   {"job5_2", "asm5_b"},
	{"job5_3", "asm5_c"},   {"lanstp1", "law2_18"}, {"lanstp2", "law2_19"},
	{"phil2_1", "phi2_05"}, {"phil2_2", "phi2_06"}, {"phil2_3", "phi2_07"},
	{"phil2_4", "phi2_08"}, {"phil2_5", "phi2_09"}, {"phil2_6", "phi2_10"},
	{"phil2_7", "phi2_11"}, {"phil2_8", "phi2_12"}, {"phil2_9", "phi2_13"},
	{"phil210", "phi2_14"}, {"phil211", "phi2_15"}, {"piss_01", "piz1_13"},
	{"piss_02", "piz1_14"}, {"piss_03", "piz1_15"}, {"piss_04", "piz1_16"},
	{"piss_05", "piz1_17"}, {"piss_06", "piz1_18"}, {"piss_07", "piz1_19"},
	{"piss_08", "piz1_20"}, {"piss_09", "piz1_21"}, {"piss_10", "piz1_22"},
	{"piss_11", "piz1_23"}, {"piss_12", "piz1_24"}, {"piss_13", "piz1_25"},
	{"piss_14", "piz1_26"}, {"piss_15", "piz1_27"}, {"piss_16", "piz1_28"},
	{"piss_17", "piz1_29"}, {"piss_18", "piz1_30"}, {"piss_19", "piz1_31"},
	{"porn1_1", "por1_04"}, {"porn1_2", "por1_05"}, {"porn1_3", "por1_06"},
	{"porn1_4", "por1_08"}, {"porn1_5", "por1_09"}, {"porn1_6", "por1_10"},
	{"porn1_7", "por1_11"}, {"porn1_8", "por1_14"}, {"porn1_9", "por1_15"},
	{"prn1_3a", "por1_07"}, {"prn1_10", "por1_16"}, {"prn1_11", "por1_17"},
	{"prn1_12", "por1_19"}, {"prn1_13", "por1_20"}, {"prn1_14", "por1_21"},
	{"prn1_15", "por1_22"}, {"prn1_16", "por1_27"}, {"prn1_17", "por1_28"},
	{"prn1_18", "por1_29"}, {"prn1_19", "por1_30"}, {"prn1_20", "por1_31"},
	{"prn1_21", "por1_7b"}, {"porn3_1", "por3_04"}, {"porn3_2", "por3_05"},
	{"porn3_3", "por3_06"}, {"porn3_4", "por3_07"}, {"rok2_01", "rock_4"},
	{"tex1_1", "tex1_3"},   {"tex1_3", "tex1_7"},   {"tex1_4", "tex1_6"},
	{"tex1_5", "tex1_9"},   {"tex1_6", "tex1_10"},
} };
const char* tables[] = { "AMBULAE", "ASSIN1", "ASSIN2", "ASSIN3", "ASSIN4", "ASSIN5",
"BANKJ1", "BANKJ2", "BANKJ3", "BANKJ4", "BARON1", "BARON2", "BARON3", "BARON4", "BARON5",
"BIKE1", "BIKE2", "BIKE3", "BMX_1", "BOATBUY", "CAP_1", "CARBUY", "COPCAR", "COUNT1", "COUNT2",
"CUBAN1", "CUBAN2", "CUBAN3", "CUBAN4", "FINALE", "FIRETRK", "GENERA1", "GENERA2", "GENERA3",
"GENERA4", "GENERA5", "HAIT1", "HAIT2", "HAIT3", "HOTEL", "ICECRE1", "ICECUT", "INTRO", "KENT1",
"KICKSTT", "LAWYER1", "LAWYER2", "LAWYER3", "LAWYER4", "MIAMI_1", "MM", "OVALRIG", "PHIL1", "PHIL2",
"PIZZA", "PORN1", "PORN2", "PORN3", "PORN4", "PROT1", "PROT2", "PROT3", "RACES", "RCHELI1", "RCPLNE1",
"RCRACE1", "ROCK1", "ROCK2", "ROCK3", "SERG1", "SERG2", "SERG3", "TAXI1", "TAXICUT", "TAXIWA1",
"TAXIWA2", "TAXIWA3"};

std::map<std::string, wchar_t*> tokens =
{
	{"TAXW1_5", L"~g~You need to be in a vehicle!"},
	{"NOTAXI", L"~g~You need a vehicle to activate this mission."},
	{"CUB4_26", L"~g~Take Pepe, head North into Little Haiti and steal a vehicle."}
};

MissionAudioData* MissionAudioNameSfxAssoc = (MissionAudioData*)0x6B0250;

const int STREAMED_SOUND_MISSION_START = 0x67;
const int STREAMED_SOUND_MISSION_END = 0x4C7;

void __fastcall Voices::LoadRandomizedAudio(cDMAudio* audio, void* edx, int slot, char* text)
{
	int index;
	while ((index = RandomNumber(STREAMED_SOUND_MISSION_START, STREAMED_SOUND_MISSION_END), index == 671));

	if (Config::voice.loopEnabled)
	{
		static int phonecall = -1;
		if (text == std::string("mobring"))
			phonecall == -1 ? phonecall = index : index = phonecall;
	}

	std::string newName = MissionAudioNameSfxAssoc[index - STREAMED_SOUND_MISSION_START].SoundName;

	if (text == std::string("rok2_01")) // Love Fist
		newName = text;

	if (Config::voice.MatchSubtitles)
	{
		for (int i = 0; i < strlen(text); i++)
			text[i] = std::tolower(text[i]);

		std::transform(newName.begin(), newName.end(), newName.begin(),
			[](unsigned char c) { return std::tolower(c); });

		std::string subtitle = subtitles.count(text) ? subtitles[text] : text;
		std::transform(subtitle.begin(), subtitle.end(), subtitle.begin(),
			[](unsigned char c) { return std::tolower(c); });

		/* Labels which return their own, causing mission text to appear */
		if (index > 637 && index < 646 || index > 119 && index < 135 || index > 187
			&& index < 191 || index == 632 || index == 770)
			voiceLines[subtitle] = "";
		else
			voiceLines[subtitle] = newName;

		if (subtitles.count(newName))
			voiceLines[subtitle] = subtitles[newName];
	}
	audio->PreloadMissionAudio(slot, newName.c_str());
}
const wchar_t* __fastcall Voices::FixSubtitles(CText* text, void* edx, char* key)
{
	if (mData.size() == 0)
		InitialiseText(text);

	std::string _key = key;
	std::transform(_key.begin(), _key.end(), _key.begin(),
		[](unsigned char c) { return std::tolower(c); });

	if (voiceLines.count(_key))
		_key = voiceLines[_key];

	std::transform(_key.begin(), _key.end(), _key.begin(),
		[](unsigned char c) { return std::toupper(c); });

	return mData[_key].c_str();
}
void Voices::UpdateText(CKeyArray& array)
{
	for (int i = 0; i < array.size; i++)
	{
		if (Config::script.Enabled)
		{
			if (tokens.count(array.data[i].szTokenName))
			{
				mData[array.data[i].szTokenName] = tokens.at(array.data[i].szTokenName);
				continue;
			}
		}
		mData[array.data[i].szTokenName] = array.data[i].offset;
	}
}
void Voices::InitialiseText(CText* text)
{
	UpdateText(text->tKeyMain);
	for (int i = 0; i < sizeof(tables) / 4; i++)
	{
		text->LoadMissionText(tables[i]);
		UpdateText(text->tKeyMission);
	}
}
void cDMAudio::PreloadMissionAudio(int slot, const char* text)
{
	plugin::CallMethod<0x5F9820>(this, slot, text);
}
char* CText::GetText(const char* key)
{
	return plugin::CallMethodAndReturn<char*, 0x584F30, CText*>(this, key);
}
char* CText::LoadMissionText(const char* text)
{
	return plugin::CallMethodAndReturn<char*, 0x585150, CText*>(this, text);
}
void Voices::Initialise()
{
	if (Config::voice.Enabled)
		plugin::patch::RedirectCall(0x45AB6B, LoadRandomizedAudio);

	if (Config::voice.Enabled || Config::script.Enabled)
	{
		plugin::patch::RedirectCall(0x44AF4B, FixSubtitles);
		plugin::patch::RedirectCall(0x45328A, FixSubtitles);
		plugin::patch::RedirectCall(0x45A645, FixSubtitles);
		plugin::patch::RedirectCall(0x44AFE7, FixSubtitles);
	}
}