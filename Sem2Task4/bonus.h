#pragma once

#ifndef BONUS_H
#define BONUS_H

#include <stdio.h>
#include "general.h"

typedef enum {

} Type;

typedef struct {
	Vector2D position;
	Vector2D velocity;
	int width;
	int height;
	Type type;
} Bonus;

#endif