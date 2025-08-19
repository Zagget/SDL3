#pragma once
#include <SDL3/SDL.h>
#include "FrameData.h"
#include <vector>
#include "GameObject.h"

class Game
{
public:
	Game(int screenWidth, int screenHeight);
	
	virtual ~Game();

	virtual void Update();
	virtual void HandleEvents();
	virtual void Render();

	void Quit();
	bool running = true;

protected:
	bool InitSDL();

	SDL_Window* win = nullptr;
	SDL_Renderer* ren = nullptr;
	std::vector<GameObject*> gameObjects;

	FrameData fdata;
	int screenWidth;
	int screenHeight;
};