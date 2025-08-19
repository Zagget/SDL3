#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
	Player(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Texture* texture) 
		: GameObject(renderer, x, y, w, h, texture) {};
	
	~Player() {};


	virtual void Update(float DeltaTime, float ScaledDeltaTime) override;

private:
	float xMove = 0;
	float yMove = 0;

	float moveScale = 5;
};