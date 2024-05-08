#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "invoker.h"
#include "painter.h"
#include "saver.h"
#include "SDL2_gfxPrimitives.h"

#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 700
#define EDGE 100

int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("PaintLite.exe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Menu* menu = (Menu*)malloc(sizeof(Menu));
    int lastSaved = 0;
    init(menu, lastSaved);
    SDL_Color color = { 255, 0, 0, 255 };
    int width = 1;


    bool quit = 0;
    bool isDrawing = 0;
    bool isDrawingFigures = 0;

    SDL_Surface** saves = (SDL_Surface**)malloc(10 * sizeof(SDL_Surface*));
    for (int i = 0; i < 10; i++) {
        saves[i] = SDL_CreateRGBSurface(0, SCREEN_WIDTH - EDGE, SCREEN_HEIGHT - EDGE, 32, 0, 0, 0, 0);
    }

    int prevX = 0;
    int prevY = 0;

    int startX = -1;
    int startY = -1;

    int endX = -1;
    int endY = -1;

    SDL_Surface* active = SDL_CreateRGBSurface(0, SCREEN_WIDTH - EDGE, SCREEN_HEIGHT - EDGE, 32, 0, 0, 0, 0);


    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.x >= EDGE && event.button.y >= EDGE) {
                        if (menu->tools[menu->currentTool].tool == PEN || menu->tools[menu->currentTool].tool == ERASER) {
                            isDrawing = 1;

                            prevX = event.button.x;
                            prevY = event.button.y;
                        }
                        if (menu->tools[menu->currentTool].tool == ELLIPS || menu->tools[menu->currentTool].tool == RECT || menu->tools[menu->currentTool].tool == LINE) {
                            isDrawingFigures = 0;

                            startX = event.button.x;
                            startY = event.button.y;

                        }

                    }
                    else {
                        Inf* inf = checkButtonClick(menu, event.button.x, event.button.y);
                        if (inf != NULL) {
                            Type type = inf->type;
                            int num = inf->num;

                            if (type == TOOL) {
                                if (num == PEN || num == ELLIPS || num == RECT || num == LINE) {
                                    switch (menu->colors[menu->currentColor].color)
                                    {
                                    case 0: setColor(&color, 255, 0, 0, 255); break;
                                    case 1: setColor(&color, 0, 255, 0, 255); break;
                                    case 2: setColor(&color, 0, 0, 255, 255); break;
                                    default: break;
                                    }
                                }
                                if (num == ERASER) {
                                    setColor(&color, 0, 0, 0, 255);
                                }
                                menu->currentTool = num;
                            }

                            if (type == COLOR) {
                                if (num == RED) {
                                    setColor(&color, 255, 0, 0, 255);
                                }
                                if (num == GREEN) {
                                    setColor(&color, 0, 255, 0, 255);
                                }
                                if (num == BLUE) {
                                    setColor(&color, 0, 0, 255, 255);
                                }
                                menu->currentColor = num;
                            }

                            if (type == WIDTH) {
                                switch (num) {
                                case ONEPIX:
                                    width = 1;
                                    break;
                                case THREEPIX:
                                    width = 3;
                                    break;
                                case FIVEPIX:
                                    width = 5;
                                    break;
                                }
                                menu->currentWidth = num;
                            }

                            if (type == GENERAL) {
                                if (num == NEW) {
                                    active = SDL_CreateRGBSurface(0, SCREEN_WIDTH - EDGE, SCREEN_HEIGHT - EDGE, 32, 0, 0, 0, 0);
                                }
                                if (num == SAVE) {
                                    copyPixels(active, saves[lastSaved], 0, 0, 0, 0);
                                    printf("%d has been written \n", lastSaved);
                                    lastSaved++;
                                    menu->lastSaved = lastSaved;
                                }
                            }

                            if (type == SAVES) {
                                copyPixels(saves[num], active, 0, 0, 0, 0);
                            }
                        }

                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.x >= EDGE && event.button.y >= EDGE) {
                        if (menu->tools[menu->currentTool].tool == PEN || menu->tools[menu->currentTool].tool == ERASER) {
                            isDrawing = 0;
                        }
                        if (menu->tools[menu->currentTool].tool == ELLIPS || menu->tools[menu->currentTool].tool == RECT || menu->tools[menu->currentTool].tool == LINE) {
                            isDrawingFigures = 1;

                            endX = event.button.x;
                            endY = event.button.y;
                        }

                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                    case SDLK_w: {
                        setColor(&color, 255, 255, 255, 255);
                        break;
                    }
                    case SDLK_c: {
                        setColor(&color, 0, 0, 0, 255);
                        break;
                    }
                    case SDLK_r: {
                        setColor(&color, 255, 0, 0, 255);
                        break;
                    }
                    case SDLK_g: {
                        setColor(&color, 0, 255, 0, 255);
                        break;
                    }
                    case SDLK_b: {
                        setColor(&color, 0, 0, 255, 255);
                        break;
                    }
                    case SDLK_s:
                        copyPixels(active, saves[lastSaved], 0, 0, 0, 0);
                        lastSaved++;
                        break;
                    case SDLK_n:
                        active = SDL_CreateRGBSurface(0, SCREEN_WIDTH - EDGE, SCREEN_HEIGHT - EDGE, 32, 0, 0, 0, 0);
                        break;
                    }
                    if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) {
                        int num = event.key.keysym.sym - SDLK_0;
                        copyPixels(saves[num], active, 0, 0, 0, 0);
                    }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, EDGE-1, 0, EDGE-1, 10000);
        SDL_RenderDrawLine(renderer, 0, EDGE-1, 10000, EDGE-1);
        drawMenu(renderer, menu, font);


        redrawPixels(renderer, active, EDGE, EDGE);
      
        if (isDrawing) {
            if (menu->tools[menu->currentTool].tool == PEN) {
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                int x, y;
                Uint32 mouseState = SDL_GetMouseState(&x, &y);

                thickLineRGBA(renderer, prevX, prevY, x, y, width, color.r, color.g, color.b, color.a);
                prevX = x;
                prevY = y;
            }
            if (menu->tools[menu->currentTool].tool == ERASER){
                int x, y;
                Uint32 mouseState = SDL_GetMouseState(&x, &y);

                thickLineRGBA(renderer, prevX, prevY, x, y, 3*width, 0, 0, 0, 255);
                prevX = x;
                prevY = y;
            }
        }
        if (isDrawingFigures && (startX != -1 && startY != -1 && endX != -1 && endY != -1)){
            if (menu->tools[menu->currentTool].tool == ELLIPS) {
                thickEllipseRGBA(renderer, (startX + endX) / 2, (startY + endY) / 2, abs(startX - endX) / 2, abs(endY - startY) / 2, color.r, color.g, color.b, color.a, width);
            }
            if (menu->tools[menu->currentTool].tool == RECT) {
                drawThickRect(renderer, startX, startY, endX, endY, color.r, color.g, color.b, color.a, width);
            }
            if (menu->tools[menu->currentTool].tool == LINE) {
                thickLineRGBA(renderer, startX, startY, endX, endY, width, color.r, color.g, color.b, color.a);
            }
            startX = -1;
            startY = -1;
            endX = -1;
            endY = -1;
        }
        SDL_RenderPresent(renderer);
        readPixelsFromScreen(renderer, active, EDGE, EDGE);
    
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}