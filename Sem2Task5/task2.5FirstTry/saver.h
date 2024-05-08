#pragma once
#ifndef SAVER_H
#define SAVER_H

#include <SDL_ttf.h>
#include <SDL.h>

void copyPixels(SDL_Surface* src, SDL_Surface* dest, int srcX, int srcY, int destX, int destY);
void readPixelsFromScreen(SDL_Renderer* renderer, SDL_Surface* surface, int startX, int startY);

#endif