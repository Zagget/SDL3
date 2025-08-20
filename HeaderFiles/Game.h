#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "FrameData.h"
#include "player.h"

class Game
{
public:
	Game(int screenWidth, int screenHeight);
	
	virtual ~Game();

	virtual void Update();
	virtual void UpdateCamera(Player* player);
	virtual void HandleEvents();
	virtual void Render();

	virtual void AddObject(GameObject* go);

	SDL_Renderer* GetRenderer() const { return ren; }
	int GetScreenWidth() const { return screenWidth; }
	int GetScreenHeight() const { return screenHeight; }
	
	void Quit();
	bool running = true;

protected:
	bool InitSDL();

	SDL_Window* win = nullptr;
	SDL_Renderer* ren = nullptr;
	Camera camera;

	std::vector<GameObject*> gameObjects;

	FrameData fdata;
	int screenWidth;
	int screenHeight;
};