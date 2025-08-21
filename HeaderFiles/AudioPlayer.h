#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_mixer.h>
#include <string>

class AudioPlayer {
public:
    AudioPlayer() = default;
    ~AudioPlayer() { Quit(); }

    bool Init();

    bool Load(const std::string& path);

    void Play(bool loop = false);
    void Stop();
    void Free();

    void Quit();

private:
    MIX_Mixer* mixer = nullptr;
    MIX_Audio* audioData = nullptr;
    MIX_Track* track = nullptr;
};
