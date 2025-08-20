#pragma once
#include <SDL3/SDL.h>
#include "Camera.h"

class GameObject {
public:
	GameObject(SDL_Renderer* renderer, int x, int y, int w, int h);
	GameObject(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Texture* texture);
	~GameObject();

	virtual void HandleEvent(const SDL_Event& e);
	virtual void Render(const Camera& cam);
	virtual void Update(float deltaTime, float scaledDeltaTime);
	virtual void SetPosition(int x, int y);
	virtual void SetMovement(float x, float y);

	float GetX() const { return rect.x; }
	float GetY() const { return rect.y; }

	float GetW() const { return rect.w; }
	float GetH() const { return rect.h; }

protected:
	SDL_Renderer* renderer = nullptr;
	SDL_FRect rect;
	SDL_Texture* texture = nullptr;

	float xMove = 0;
	float yMove = 0;
	float moveScale = 5;
};