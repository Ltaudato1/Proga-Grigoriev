#pragma once
#ifndef PAINTER_H
#define PAINTER_H

#include <Windows.h>
#include "geometry.h"

void drawTriangle(HDC hdc, TRIANGLE triangle);
void drawRubberBand(HWND hwnd, POINT p1);
void drawIteration(HDC hdc, int it);

#endif