#include <SDL.h>
#include <stdio.h>
#include "player.h"
#include "level.h"
#include "bonus.h"
#include "menu.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    initPaddle(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT - 20, 100, 10);
    initBall(10, -300, -300);
    initLevel();
    initIcon(renderer);

    SDL_Event event;
    int running = 1;
    Uint32 lastTime = SDL_GetTicks();

    MenuState currentState = MENU;
    initMenu();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (float)(currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (currentState == GAME) {
                if (event.type == SDL_KEYDOWN) {
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
                    case SDLK_ESCAPE:
                        running = 0;
                        break;
                    }
                }
            }
            else if (currentState == MENU) {
                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        movePointer(UP);
                        break;
                    case SDLK_DOWN:
                        movePointer(DOWN);
                        break;
                    case SDLK_RETURN:
                        processClick(&currentState, &running);
                        break;
                    }
                }
            }
        }

        if (currentState == GAME) {
            updatePlayer(deltaTime);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            drawPaddle(renderer);
            drawBall(renderer);
            redrawLevel(renderer);
            redrawBonus(renderer, deltaTime);
            drawLives(renderer);

            if (!checkHp()) {
                running = 0;
            }

            SDL_RenderPresent(renderer);
        }
        else {
            drawMenu(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
