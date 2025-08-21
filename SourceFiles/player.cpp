#include "player.h"
#include <iostream>

void Player::Update(float deltaTime, float scaledDeltaTime) {
	const bool* keys = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();

	yMove = 0;
	xMove = 0;

	if (keys[SDL_SCANCODE_W])
		yMove = -1;
	if (keys[SDL_SCANCODE_A])
		xMove = -1;
	if (keys[SDL_SCANCODE_S])
		yMove = 1;
	if (keys[SDL_SCANCODE_D])
		xMove = 1;

	SetMovement();

	printf("\rplayerPos X: %.0f Y: %.0f ", rect.x, rect.y);
}