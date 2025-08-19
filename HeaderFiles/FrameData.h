#pragma once
#include <SDL3/SDL.h>

struct FrameData {
    int framecnt = 0;
    const Uint32 frameDelay = 1000 / 60; // 60 FPS
    Uint32 frameStart = 0;
    Uint32 frameTime = 0;
    Uint64 lastTime = 0;
    float timeScale = 1.f;
    float deltaTime = 0;
    float scaledDeltaTime = 0;
};