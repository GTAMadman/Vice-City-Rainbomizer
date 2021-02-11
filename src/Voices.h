#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"
#include "CRunningScript.h"
#include "CTheScripts.h"
#include <filesystem>
#include <map>

struct cDMAudio
{
	void PreloadMissionAudio(int slot, const char* text);
};
struct CKeyEntry
{
	wchar_t* offset;
	char szTokenName[8];
};
struct CData
{
	char* data;
	int   size;
};
struct CKeyArray
{
	CKeyEntry* data;
	short size;
};
struct CText
{
	CKeyArray tKeyMain;
	CData     tDataMain;
	CKeyArray tKeyMission;
	CData     tDataMission;

	char* GetText(const char* key);
	char* LoadMissionText(const char* text);
};

class Voices : Functions
{
public:
	static void Initialise();
private:
	inline static std::map<std::string, std::wstring> mData;
	inline static std::unordered_map<std::string, std::string> voiceLines;
	static void __fastcall LoadRandomizedAudio(cDMAudio* audio, void* edx, int slot, char* text);
	static const wchar_t* __fastcall FixSubtitles(CText* text, void* edx, char* key);
	static void UpdateText(CKeyArray& array);
	static void InitialiseText(CText* text);
};