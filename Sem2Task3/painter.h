#pragma once
#ifndef PAINTER_H
#define PAINTER_H

#include <Windows.h>
#include "structs.h"

void drawWindow(Window* window, Button* buttons, HINSTANCE hInstance, int nCmdShow, int buttonsCounter);
void drawAlign(Button* button, COLORREF color);
void redrawButton(Button* button);

#endif