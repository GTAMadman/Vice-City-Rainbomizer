#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"
#include "CRunningScript.h"
#include "CTheScripts.h"
#include <filesystem>

struct cDMAudio
{
	void PreloadMissionAudio(int slot, const char* text);
};
struct CText
{
	char* GetText(const char* key);
	char* LoadMissionText(const char* text);
};

class voices : Functions
{
public:
	static void Initialise();
private:
	static CText* previousText;
	static std::string previousTable;
	static void __fastcall LoadRandomizedAudio(cDMAudio* audio, void* edx, int slot, char* text);
	static char* __fastcall FixSubtitles(CText* text, void* edx, char* key);
	static void LoadTable(CText* text, char* key);
	static std::unordered_map<std::string, std::string> voiceLines;
	static void __fastcall UseGXTTable(CText* text, void* edx, const char* table);
	static char* __fastcall FixDeathRowText(CText* text, void* edx, char* key);
	static void __fastcall HasAudioFinished(CRunningScript* script, void* edx, char flag);
};