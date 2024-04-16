#include "menu.h"
#include "general.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

#define NUM_OF_BUTTONS 2

TTF_Font* font;

MenuItem buttons[NUM_OF_BUTTONS];
int currentButton = 0;

void initMenu() {
    TTF_Init();

    font = TTF_OpenFont("font.ttf", 24);

    buttons[0] = START;
    buttons[1] = QUIT;
}

void destroyMenu() {
    TTF_CloseFont(font);
    TTF_Quit();
}

void drawText(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL) {
        printf("Failed to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL) {
            printf("Failed to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else {
            SDL_Rect rect = { x, y, surface->w, surface->h };
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}


void drawMenu(SDL_Renderer* renderer) {
    SDL_Color startColor = { 255, 255 * (buttons[currentButton] != START), 255 * (buttons[currentButton] != START), 255};
    drawText(renderer, "Start", SCREEN_WIDTH / 2 - 30, 210, startColor);

    SDL_Color quitColor = { 255, 255 * (buttons[currentButton] != QUIT), 255 * (buttons[currentButton] != QUIT), 255};
    drawText(renderer, "Quit", SCREEN_WIDTH / 2 - 25, 310, quitColor);

    SDL_RenderPresent(renderer);
}



MenuItem checkButtonClick(int x, int y) {
    if (x > SCREEN_WIDTH / 2 - 50 && x < SCREEN_WIDTH / 2 + 50 && y > 200 && y < 250) {
        return START;
    }

    else if (x > SCREEN_WIDTH / 2 - 50 && x < SCREEN_WIDTH / 2 + 50 && y > 300 && y < 350) {
        return QUIT;
    }
    return -1;
}

void processClick(MenuState* currentState, int* running) {
    switch (buttons[currentButton]) {
    case START:
        *currentState = GAME;
        destroyMenu();
        break;
    case QUIT:
        *running = 0;
        destroyMenu();
        break;
    }
}

void movePointer(Direction dir) {
    switch (dir) {
    case DOWN:
        currentButton = (currentButton + 1) % 2;
        break;
    case UP:
        currentButton = (currentButton - (currentButton > 0) + (currentButton == 0));
        break;
    }
}
