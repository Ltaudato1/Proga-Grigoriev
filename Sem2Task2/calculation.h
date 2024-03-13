#pragma once
#ifndef CALCULATION_H
#define CALCULATION_H

#include <Windows.h>

typedef enum
{
	PLUS, MINUS
} iterationType;

POINT calcFirstIteration(HWND hwnd, POINT p1, POINT p2);
void proceedIteration(int iteration);
TRIANGLE getIteration(int i, int j);
void handleIteration(HWND hwnd, iterationType type);
void handle(HDC hdc);

#endif