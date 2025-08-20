#include "GameObject.h"
#include <cmath>

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


void GameObject::HandleEvent(const SDL_Event& e)
{

}

void GameObject::Render() {

    if (texture)
        SDL_RenderTexture(renderer, texture, NULL, &rect);
    else
        SDL_RenderFillRect(renderer, &rect);
}

void GameObject::Update(float deltaTime, float scaledDeltaTime)
{
}

void GameObject::SetPosition(int x, int y) {
    rect.x = (float)x;
    rect.y = (float)y;
}

void normalizeMovement(float& x, float& y) {
    float length = std::sqrt(x * x + y * y);
    if (length > 0.0f) {
        x /= length;
        y /= length;
    }
}

void GameObject::SetMovement(float x, float y) {
    normalizeMovement(xMove, yMove);

    rect.x += xMove * moveScale;
    rect.y += yMove * moveScale;
}