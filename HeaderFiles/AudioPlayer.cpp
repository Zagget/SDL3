#include <SDL3/SDL_mixer.h>
#include <iostream>
#include "AudioPlayer.h"

bool AudioPlayer::Init() {
	if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) {
		std::cerr << "SDL_InitSubSystem failed: " << SDL_GetError() << "\n";
		return false;
	}
	if (!MIX_Init()) {
		std::cerr << "MIX_Init failed: " << SDL_GetError() << "\n";
		return false;
	}
	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, new SDL_AudioSpec{ SDL_AudioFormat::SDL_AUDIO_F32,1,44100 });
	if (!mixer) {
		std::cerr << "MIX_CreateMixerDevice failed: " << SDL_GetError() << "\n";
		return false;
	}
	return true;
}
/// <summary>
/// load file at path to memory
/// </summary>
/// <param name="path"></param>
/// <returns></returns>
bool AudioPlayer::Load(const std::string& path) {
	Free();
	audioData = MIX_LoadAudio(mixer, path.c_str(), false);
	if (!audioData) {
		std::cerr << "MIX_LoadAudio failed: " << SDL_GetError() << "\n";
		return false;
	}
	return true;
}
/// <summary>
/// play loaded file
/// </summary>
/// <param name="loop"></param>
void AudioPlayer::Play(bool loop) {
	if (!mixer || !audioData) return;

	track = MIX_CreateTrack(mixer);
	if (!track) {
		std::cerr << "MIX_CreateTrack failed: " << SDL_GetError() << "\n";
		return;
	}

	if (!MIX_SetTrackAudio(track, audioData)) {
		std::cerr << "MIX_SetTrackAudio failed: " << SDL_GetError() << "\n";
		return;
	}

	// loop = -1 for infinite, or 0 for once
	if (!MIX_PlayTrack(track, loop ? -1 : 0)) {
		std::cerr << "MIX_PlayTrack failed: " << SDL_GetError() << "\n";
	}
}

void AudioPlayer::Stop() {
	if (track) {
		MIX_StopTrack(track, 0);
		track = 0;
	}
}
/// <summary>
/// free memory
/// </summary>
void AudioPlayer::Free() {
	if (audioData) {
		MIX_DestroyAudio(audioData);
		audioData = nullptr;
	}
}

void AudioPlayer::Quit() {
	Stop();
	Free();
	if (mixer) {
		MIX_DestroyMixer(mixer);
		mixer = nullptr;
	}
	MIX_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}