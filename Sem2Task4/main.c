#include <SDL.h>
#include <stdio.h>
#include "player.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    initPaddle(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 20, 100, 10);
    initBall(10, -300, -300);

    SDL_Event event;
    int running = 1;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (float)(currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    movePaddle(LEFT);
                    break;
                case SDLK_RIGHT:
                    movePaddle(RIGHT);
                    break;
                case SDLK_SPACE:
                    launchBall();
                    break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    stopPaddle();
                    break;
                case SDLK_RIGHT:
                    stopPaddle();
                    break;
                }
            }
        }

        updatePlayer(deltaTime);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Очистка экрана (установка цвета черного)
        SDL_RenderClear(renderer);

        drawPaddle(renderer);
        drawBall(renderer);

        SDL_RenderPresent(renderer); // Обновление экрана
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
