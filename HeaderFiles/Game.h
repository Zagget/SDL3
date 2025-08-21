#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "FrameData.h"
#include "player.h"
#include "WorldData.h"
#include "AudioPlayer.h"

class Game
{
public:
	Game(int screenWidth, int screenHeight);
	
	virtual ~Game();

	void Update();
	void CheckCollision();
	void UpdateCamera(Player* player);
	void HandleEvents();
	void Render();

	void AddObject(GameObject* go);

	SDL_Renderer* GetRenderer() const { return ren; }
	int GetScreenWidth() const { return screenWidth; }
	int GetScreenHeight() const { return screenHeight; }
	
	void Quit();
	bool running = true;

protected:
	bool InitSDL();

	SDL_Window* win = nullptr;
	SDL_Renderer* ren = nullptr;
	SDL_Texture* background = nullptr;
	Camera camera;

	std::vector<GameObject*> gameObjects;

	FrameData fData;
	WorldData wData;
	AudioPlayer audio;

	int screenWidth;
	int screenHeight;
};