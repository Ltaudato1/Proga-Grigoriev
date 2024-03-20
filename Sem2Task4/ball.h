#pragma once

#ifndef BALL_H
#define BALL_H

#include <stdio.h>
#include "general.h"

typedef struct {
	Vector2D currentPosition;
	Vector2D velocity;
	float radius;
} Ball;

#endif