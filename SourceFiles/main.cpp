#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>
#include "Game.h"
#include "player.h"


int main(int argc, char** argv) {
    
    Game game(1000, 800);
    
    SDL_Renderer* ren = game.GetRenderer();
    
    SDL_Texture* playerTexture = IMG_LoadTexture(ren, "confusedman.png");
    if (!playerTexture) {
        std::cerr << "playerTexture error: " << SDL_GetError() << '\n';
    }

    int middleX = game.GetScreenWidth() / 2 - 200 / 2;
    int middleY = game.GetScreenHeight() / 2 - 200 / 2;

    Player* player = new Player(ren, middleX, middleY, 200, 200, playerTexture);
    game.AddObject(player);

    while (game.running) {
        game.Update();
    }
}


//float xMove, yMove;
//float moveScale = 0.05;

//bool running = true;
//SDL_Event ev;
//while (running) {
//    while (SDL_PollEvent(&ev)) {
//        if (ev.key.key == SDLK_ESCAPE) {
//            running = false;
//        }
//        if (ev.type == SDL_EVENT_QUIT) {
//            running = false;
//        }
//    }

//    // Polling
//    const bool* keys = SDL_GetKeyboardState(NULL);
//    SDL_PumpEvents();


//    //move sprite
//    xMove = 0;
//    yMove = 0;

//    if (keys[SDL_SCANCODE_W])
//        yMove = -1;
//    if (keys[SDL_SCANCODE_A])
//        xMove = -1;
//    if (keys[SDL_SCANCODE_S])
//        yMove = 1;
//    if (keys[SDL_SCANCODE_D])
//        xMove = 1;

//    xPos += xMove * moveScale;
//    yPos += yMove * moveScale;

//    if (xPos < 0) xPos = 0;
//    if (yPos < 0) yPos = 0;
//    if (xPos > width - 100) xPos = width - 100;
//    if (yPos > height - 100) yPos = height - 100; 

//    //clear last frame
//    SDL_RenderClear(ren);

//    // draw calls

//    //make rect to render sprite into
//    SDL_FRect* dst = new SDL_FRect{ xPos,yPos,100,100};
//    SDL_RenderTexture(ren, sprite, NULL, dst);

//    SDL_RenderPresent(ren);
//}