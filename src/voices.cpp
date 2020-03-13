#include "voices.h"

std::vector<std::string> voices::sounds;
void voices::PreloadMissionAudio(uint16_t* audio, int slot, char* text)
{
	plugin::CallMethod<0x5F9820>(audio, slot, text);
}
void __fastcall voices::LoadRandomizedAudio(uint16_t* audio, void* edx, int slot, char* text)
{
	char* sound;
	int index = RandomNumber(0, sounds.size() - 1);
	strcpy(sound, sounds[index].c_str());

	PreloadMissionAudio(audio, slot, text);
}
void voices::InitialiseSounds()
{
	for (auto& files : std::filesystem::directory_iterator(plugin::paths::GetGameDirRelativePathA("Audio/")))
	{
		if (files.path().extension() == ".wav")
		{
			std::string sound = files.path().filename().string();

			size_t index = sound.find_last_of(".");
			std::string fileName = sound.substr(0, index);

			sounds.push_back(fileName);
		}
	}
}
void voices::Initialise()
{
	if (Config::VoiceLineRandomizer::Enabled)
	{
		plugin::patch::RedirectCall(0x45AB6B, LoadRandomizedAudio);

		if (sounds.size() == 0)
			InitialiseSounds();
	}
}