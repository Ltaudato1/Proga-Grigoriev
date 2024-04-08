#pragma once

#ifndef GENERAL_H
#define GENERAL_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

typedef struct {
	float x;
	float y;
} Vector2D;

typedef struct {
	float x1, y1;
	float x2, y2;
} Object;

typedef char bool;
#define true 1;
#define false 0;

#endif