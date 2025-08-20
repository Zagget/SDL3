#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "player.h"
#include "Enemy.h"

int main(int argc, char** argv) {

	Game game(1000, 800);

	SDL_Renderer* ren = game.GetRenderer();

	SDL_Texture* playerTexture = IMG_LoadTexture(ren, "confusedman.png");
	if (!playerTexture) {
		std::cerr << "playerTexture error: " << SDL_GetError() << '\n';
	}

	SDL_Texture* enemyTexture = IMG_LoadTexture(ren, "disgustedoldman.png");
	if (!enemyTexture) {
		std::cerr << "playerTexture error: " << SDL_GetError() << '\n';
	}

	int middleX = game.GetScreenWidth() / 2 - 200 / 2;
	int middleY = game.GetScreenHeight() / 2 - 200 / 2;

	int topLeftX = -game.GetScreenWidth() - 200 / 2;
	int topleftY = -game.GetScreenHeight() - 200 / 2;

	Player* player = new Player(ren, 0, 0, 200, 200, playerTexture);
	Enemy* enemy = new Enemy(ren, middleX, middleY, 200, 200, enemyTexture);

	game.AddObject(player);
	game.AddObject(enemy);

	while (game.running) {
		game.Update();
	}

	game.Quit();
}