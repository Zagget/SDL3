#include "GameObject.h"
#include <cmath>
#include "WorldData.h"
#include <iostream>

GameObject::GameObject(SDL_Renderer* renderer, int x, int y, int w, int h)
    : renderer(renderer) {
    rect = { (float)x, (float)y, (float)w, (float)h };
    texture = nullptr;
}
GameObject::GameObject(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Texture* texture)
    : renderer(renderer), texture(texture) {
    rect = { (float)x, (float)y, (float)w, (float)h };
}
GameObject::~GameObject() {}


void GameObject::HandleEvent(const SDL_Event& e){

}

void GameObject::Render(const Camera& cam) {
    SDL_FRect screenRect = cam.WorldToScreen(rect);

    if (texture) {
        // Flash
        if (flashTimer > 0) {
            SDL_SetTextureColorMod(texture, 255, 255, 255); 
            SDL_SetTextureAlphaMod(texture, 255);           
            flashTimer--;
        }
        else {
            SDL_SetTextureColorMod(texture, 150, 150, 150); 
            SDL_SetTextureAlphaMod(texture, 255);
        }

        SDL_RenderTexture(renderer, texture, NULL, &screenRect);
    }
    else {
        if (flashTimer > 0) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            flashTimer--;
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        SDL_RenderFillRect(renderer, &screenRect);
    }
}

void GameObject::Update(float deltaTime, float scaledDeltaTime) {
}

bool GameObject::CheckCollision(const GameObject& other) const {
    return (rect.x < other.rect.x + other.rect.w &&
        rect.x + rect.w > other.rect.x &&
        rect.y < other.rect.y + other.rect.h &&
        rect.y + rect.h > other.rect.y);
}

void GameObject::OnCollision() {
    rect.x = lastPos.x;
    rect.y = lastPos.y;

    flashTimer = 5;

}

void normalizeMovement(float& x, float& y) {
    float length = std::sqrt(x * x + y * y);
    if (length > 0.0f) {
        x /= length;
        y /= length;
    }
}

void GameObject::SetMovement() {
    normalizeMovement(xMove, yMove);

    lastPos = { rect.x, rect.y };

    rect.x += xMove * moveScale;
    rect.y += yMove * moveScale;

    // clamp to world bounds
    if (rect.x < 0) rect.x = 0;
    if (rect.x > wData.worldW - rect.w) rect.x = wData.worldW - rect.w;

    if (rect.y < 0) rect.y = 0;
    if (rect.y > wData.worldH - rect.h) rect.y = wData.worldH - rect.h;
}