#pragma once
#include "GameObject.h"

class Enemy : public GameObject {
public:
	Enemy(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Texture* texture)
		: GameObject(renderer, x, y, w, h, texture) {
	};

	~Enemy() {}

	virtual void Update(float deltaTime, float scaledDeltaTime) override;
	virtual void RandomDirection();
};