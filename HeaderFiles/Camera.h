#pragma once
#include <SDL3/SDL.h>

class Camera {
public:           
    Camera(float x, float y) : x(x), y(y) {}

    SDL_FRect WorldToScreen(const SDL_FRect& worldRect) const {
        return {
            worldRect.x - x,
            worldRect.y - y,
            worldRect.w,
            worldRect.h
        };
    }

    void SetPosition(float newX, float newY) {
        x = newX;
        y = newY;
    }

    float GetX() const { return x; }
    float GetY() const { return y; }

private:
    float x, y;
    int screenW = 0, screenH = 0;
    float worldW = 0.0f, worldH = 0.0f;
};