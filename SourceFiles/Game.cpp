#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "GameObject.h"
#include "FrameData.h"

Game::Game(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight)
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

    SDL_SetRenderDrawColor(ren, 2, 75, 120, 255);
    std::cerr << "Init Done" << '\n';

    return true;
}

Game::~Game() 
{
    if (ren) 
        SDL_DestroyRenderer(ren);
    if (win) 
        SDL_DestroyWindow(win);
    
    SDL_Quit();
}

void Game::Update() 
{
    std::cerr << "In Update" << '\n';

    while (running) 
    {
        Uint64 now = SDL_GetTicks();
        fdata.deltaTime = (now - fdata.lastTime) / 1000.0f; //seconds
        fdata.lastTime = now;
        
        //Time scale
        fdata.scaledDeltaTime = fdata.deltaTime * fdata.timeScale;

        Render();
        HandleEvents();

        //delay to fps target
        fdata.frameStart = SDL_GetTicks();
        fdata.framecnt++;
        fdata.frameTime = SDL_GetTicks() - fdata.frameStart;

        if (fdata.frameTime < fdata.frameDelay) {
            SDL_Delay(fdata.frameDelay - fdata.frameTime);
        }
    }
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
    //clear last frame
    SDL_RenderClear(ren);

    for (GameObject* go : gameObjects) {
        go->Update(fdata.deltaTime, fdata.scaledDeltaTime);
    }

    SDL_RenderPresent(ren);
}


void Game::Quit() 
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}