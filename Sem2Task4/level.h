#pragma once

#ifndef LEVEL_H
#define LEVEL_H

#include <stdio.h>
#include "general.h"
#define MAX_BLOCKS 100

typedef struct {
    Vector2D position;
    int strength; 
    int active;   
} Block;

typedef struct {
    Block blocks[MAX_BLOCKS];
    int numBlocks;
} Level;

#endif