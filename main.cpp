#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>

int main(int argc, char** argv) {

    int width = 1200;
    int height = 1000;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);
    SDL_Window* win = SDL_CreateWindow("SDL3 Demo", width, height, 0);
    SDL_Renderer* ren = SDL_CreateRenderer(win, NULL);

    //background color
    SDL_SetRenderDrawColor(ren, 2, 75, 120, 255);

    SDL_Texture* sprite = IMG_LoadTexture(ren, "confusedman.png");
    if (!sprite) {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << '\n';
    }

    float startingXPos = width / 2 - 50;
    float startingYPos = height / 2 - 50;

    float xPos = startingXPos;
    float yPos = startingYPos;

    float xMove, yMove;
    float moveScale = 0.05;

    bool running = true;
    SDL_Event ev;
    while (running) {
        while (SDL_PollEvent(&ev)) {
            if (ev.key.key == SDLK_ESCAPE) {
                running = false;
            }
            if (ev.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        // Polling
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

        xPos += xMove * moveScale;
        yPos += yMove * moveScale;

        if (xPos < 0) xPos = 0;
        if (yPos < 0) yPos = 0;
        if (xPos > width - 100) xPos = width - 100;
        if (yPos > height - 100) yPos = height - 100; 

        //clear last frame
        SDL_RenderClear(ren);

        // draw calls

        //make rect to render sprite into
        SDL_FRect* dst = new SDL_FRect{ xPos,yPos,100,100};
        SDL_RenderTexture(ren, sprite, NULL, dst);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}