#include "GameObject.h"
#include <cmath>
#include "WorldData.h"

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

    if (texture)
        SDL_RenderTexture(renderer, texture, NULL, &screenRect);
    else
        SDL_RenderFillRect(renderer, &screenRect);
}

void GameObject::Update(float deltaTime, float scaledDeltaTime) {
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

    rect.x += xMove * moveScale;
    rect.y += yMove * moveScale;

    // Check collision

    // clamp to world bounds
    if (rect.x < 0) rect.x = 0;
    if (rect.x > wData.worldW) rect.x = wData.worldW;

    if (rect.y < 0) rect.y = 0;
    if (rect.y > wData.worldH) rect.y = wData.worldH;
}