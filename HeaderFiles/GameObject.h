#pragma once
#include <SDL3/SDL.h>

class GameObject {
public:
	GameObject(SDL_Renderer* renderer, int x, int y, int w, int h);
	GameObject(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Texture* texture);
	~GameObject();

	virtual void HandleEvent(const SDL_Event& e);
	virtual void Render();
	virtual void Update(float DeltaTime, float ScaledDeltaTime);
	virtual void SetPosition(int x, int y);

protected:
	SDL_Renderer* renderer = nullptr;
	SDL_FRect rect;
	SDL_Texture* texture = nullptr;
};