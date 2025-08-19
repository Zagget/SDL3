#include "player.h"
#include <iostream>

void Player:: Update(float DeltaTime, float ScaledDeltaTime) {

	const bool* keys = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();

	//move sprite
	xMove = 0;
	yMove = 0;

	if (keys[SDL_SCANCODE_W])
	    yMove = -1;
	if (keys[SDL_SCANCODE_A])
	    xMove = -1;
	if (keys[SDL_SCANCODE_S])
	    yMove = 1;
	if (keys[SDL_SCANCODE_D])
	    xMove = 1;

	std::cerr << "Update Player " << xMove << '\n';
	rect.x += xMove * moveScale;
	rect.y += yMove * moveScale;

	// bounds
	/*if (xPos > width - 100) xPos = width - 100;
	if (yPos > height - 100) yPos = height - 100; */


	//SDL_RenderTexture(ren, sprite, NULL, dst);
}