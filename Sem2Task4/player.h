#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "general.h"
#include <stdio.h>

typedef struct {
    Vector2D position;
    float width;
    float height;
    float speed;
} Paddle;

#endif
