#pragma once

#ifndef BONUS_H
#define BONUS_H

#include <stdio.h>
#include "general.h"
#include <SDL.h>

typedef enum {
	PADDLE_PLUS_WIDTH, EXTRA_LIFE
} Type;

typedef struct {
	Vector2D position;
	float velocityY;
	int width;
	int height;
	Type type;
} Bonus;

void dropBonus(float x, float y);
void redrawBonus(SDL_Renderer* renderer, float deltaTime);
void killBonus();

#endif