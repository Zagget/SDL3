#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "player.h"
#include "Enemy.h"
#include "WorldData.h"

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

	WorldData wData;

	int middleX = wData.worldW / 2;
	int middleY = wData.worldH / 2;

	Player* player = new Player(ren, middleX, middleY, 200, 200, playerTexture);

	Enemy* enemy1 = new Enemy(ren, middleX - 400, middleY, 200, 200, enemyTexture);
	Enemy* enemy2 = new Enemy(ren, middleX + 400, middleY, 200, 200, enemyTexture);

	game.AddObject(player);

	game.AddObject(enemy1);
	game.AddObject(enemy2);

	while (game.running) {
		game.Update();
	}

	game.Quit();
}