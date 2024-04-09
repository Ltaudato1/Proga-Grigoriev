#pragma once

#ifndef LEVEL_H
#define LEVEL_H

#include <stdio.h>
#include <SDL.h>
#include "general.h"

typedef struct {
    Vector2D position;
    float width;
    float height;
    int strength; 
    bool active;   
} Block;

typedef struct {
    Block* blocks;
    int numBlocks;
    int numActive;
} Level;

void initLevel();
void redrawLevel(SDL_Renderer* renderer);
void killBlock(Block* block);

#endif