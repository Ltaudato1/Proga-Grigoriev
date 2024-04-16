#pragma once

#ifndef MENU_H
#define MENU_H

#include <SDL.h>

typedef enum {
    START,
    QUIT
} MenuItem;

typedef enum {
    UP, DOWN
} Direction;

typedef enum {
    MENU,
    GAME
} MenuState;

typedef struct {
    MenuItem item;
    SDL_Rect rect;
} MenuButton;

void drawMenu(SDL_Renderer* renderer);
void initMenu();
void destroyMenu();
void movePointer(Direction dir);
void processClick(MenuState* currentState, int* running);
MenuItem checkButtonClick(int x, int y);

#endif