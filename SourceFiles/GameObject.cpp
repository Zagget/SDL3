#include "GameObject.h"

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

void GameObject::Update(float DeltaTime, float ScaledDeltaTime)
{
}

void GameObject::SetPosition(int x, int y) {
    rect.x = (float)x;
    rect.y = (float)y;
}