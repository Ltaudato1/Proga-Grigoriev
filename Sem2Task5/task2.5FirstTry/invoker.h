#pragma once

#ifndef INVOKER_H
#define INVOKER_H

#include <SDL_ttf.h>
#include <SDL.h>
#include "general.h"

TTF_Font* font;

void setRect(SDL_Rect* rect, int x, int y, int width, int height);
void setColor(SDL_Color* color, int r, int g, int b, int a);
void init(Menu* menu, int lastSaved);
Inf* checkButtonClick(Menu* menu, int x, int y);

#endif