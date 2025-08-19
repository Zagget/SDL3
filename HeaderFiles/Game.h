#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "FrameData.h"
#include "GameObject.h"

class Game
{
public:
	Game(int screenWidth, int screenHeight);
	
	virtual ~Game();

	virtual void Update();
	virtual void HandleEvents();
	virtual void Render();

	SDL_Renderer* GetRenderer();
	virtual void AddObject(GameObject* go);
	int GetScreenWidth() const { return screenWidth; }
	int GetScreenHeight() const { return screenHeight; }
	
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