#pragma once
#ifndef PAINTER_H
#define PAINTER_H

#include <SDL_ttf.h>
#include <SDL.h>
#include "general.h"

void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
void redrawPixels(SDL_Renderer* renderer, SDL_Surface* surface, int x, int y);
void drawThickRect(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int width);
void drawEllipse(SDL_Renderer* renderer, int x0, int y0, int radiusX, int radiusY);
void drawThickEllipse(SDL_Renderer* renderer, int x0, int y0, int radiusX, int radiusY, int w);
void drawMenu(SDL_Renderer* renderer, Menu* menu, TTF_Font* font);

#endif