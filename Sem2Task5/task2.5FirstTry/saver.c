#include <SDL_ttf.h>
#include <SDL.h>
#include <stdio.h>
#include <string.h>

void copyPixels(SDL_Surface* src, SDL_Surface* dest, int srcX, int srcY, int destX, int destY) {
    SDL_Rect srcRect = { srcX, srcY, src->w, src->h };
    SDL_Rect destRect = { destX, destY, src->w, src->h };

    SDL_BlitSurface(src, &srcRect, dest, &destRect);
}

void readPixelsFromScreen(SDL_Renderer* renderer, SDL_Surface* surface, int startX, int startY) {
    SDL_Rect rect;
    rect.x = startX;
    rect.y = startY;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderReadPixels(renderer, &rect, surface->format->format, surface->pixels, surface->pitch);
}