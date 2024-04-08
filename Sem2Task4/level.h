#pragma once

#ifndef LEVEL_H
#define LEVEL_H

#include <stdio.h>
#include <Windows.h>
#include "general.h"

typedef struct {
    Vector2D position;
    int strength; 
    bool active;   
} Block;

typedef struct {
    Block* blocks;
    int numBlocks;
} Level;

void initLevel();

#endif