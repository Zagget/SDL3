#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "GameObject.h"
#include "FrameData.h"
#include "player.h"

Game::Game(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
    camera(screenWidth / 2.0f, screenHeight / 2.0f)
{
    if (!InitSDL()) 
    {
        running = false;
    }
}

bool Game::InitSDL() 
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) == 0) {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << '\n';
        return false;
    }

    win = SDL_CreateWindow("SDL3 Demo", screenWidth, screenHeight, 0);
    if (!win) {
        std::cerr << "SDL CreateWindow: " << SDL_GetError() << '\n';
        return false;
    }

    ren = SDL_CreateRenderer(win, NULL);
    if (!ren) {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << '\n';
        return false;
    }

    background = IMG_LoadTexture(ren, "background.png");
    if (!background) {
        std::cerr << "background Texture error: " << SDL_GetError() << '\n';
    }

    std::cerr << "Init Done" << '\n';

    return true;
}

Game::~Game() 
{
    if (ren) 
        SDL_DestroyRenderer(ren);
    if (win) 
        SDL_DestroyWindow(win);
    
    for (GameObject* go : gameObjects) {
        delete go;
    }
    gameObjects.clear();
    
    SDL_Quit();
}

void Game::Update() 
{
    printf("In Update'\n'");

    while (running) 
    {
        Uint64 now = SDL_GetTicks();
        fData.deltaTime = (now - fData.lastTime) / 1000.0f;
        fData.lastTime = now;
        
        fData.scaledDeltaTime = fData.deltaTime * fData.timeScale;

        HandleEvents();

        // Update all gos
        for (GameObject* go : gameObjects) {
            go->Update(fData.deltaTime, fData.scaledDeltaTime);
        }

        CheckCollision();

        // Update camera
        if (!gameObjects.empty()) {
            Player* player = dynamic_cast<Player*>(gameObjects[0]);
            if (player) {
                UpdateCamera(player);
            }
        }

        Render();

        // Delay to fps target
        fData.frameStart = SDL_GetTicks();
        fData.framecnt++;
        fData.frameTime = SDL_GetTicks() - fData.frameStart;

        if (fData.frameTime < fData.frameDelay) {
            SDL_Delay(fData.frameDelay - fData.frameTime);
        }
    }
}

void Game::CheckCollision() {
    int goAmount = gameObjects.size();

    for (int i = 0; i < goAmount; ++i) {
        GameObject* a = gameObjects[i];

        for (int j = i + 1; j < goAmount; ++j) {
            GameObject* b = gameObjects[j];

            if (a->CheckCollision(*b)) {
                a->OnCollision();
                b->OnCollision();
            }
        }
    }
}

void Game::UpdateCamera(Player* player) {
    if (!player) return;

    float targetX = player->GetX() - screenWidth / 2 + player->GetW() / 2;
    float targetY = player->GetY() - screenHeight / 2 + player->GetH() / 2;

    // Smoothness
    float lerpFactor = 0.07f;

    float camX = camera.GetX();
    float camY = camera.GetY();

    // Lerp
    camX = camX + (targetX - camX) * lerpFactor;
    camY = camY + (targetY - camY) * lerpFactor;

    camera.SetPosition(camX, camY);
}

void Game::HandleEvents()
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        if (ev.type == SDL_EVENT_KEY_DOWN && ev.key.key == SDLK_ESCAPE)
        {
            running = false;
        }

        if (ev.type == SDL_EVENT_QUIT)
        {
            running = false;
        }
    }
}

void Game::Render() 
{
    SDL_RenderClear(ren);

    if (background) {
        SDL_FRect bgRect = { -camera.GetX(), -camera.GetY(), wData.worldW, wData.worldH};
        SDL_RenderTexture(ren, background, nullptr, &bgRect);
    }

    for (GameObject* go : gameObjects) {
        go->Render(camera);
    }

    SDL_RenderPresent(ren);
}

void Game::AddObject(GameObject* go) {
    gameObjects.push_back(go);
}

void Game::Quit() 
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}