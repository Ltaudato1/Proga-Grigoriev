#include <SDL_ttf.h>
#include <SDL.h>
#include <stdio.h>
#include <string.h>

#include "invoker.h"
#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 700

void redrawPixels(SDL_Renderer* renderer, SDL_Surface* surface, int x, int y) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture) {
        SDL_Rect destRect = { x, y, surface->w, surface->h };
        SDL_RenderCopy(renderer, texture, NULL, &destRect);
        SDL_DestroyTexture(texture);
    }
    else {
        printf("Failed to create texture from surface: %s\n", SDL_GetError());
    }
}

void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	if (surface == NULL) {
		printf("Failed to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) {
			printf("Failed to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			SDL_Rect rect = { x, y, surface->w, surface->h };
			SDL_RenderCopy(renderer, texture, NULL, &rect);
			SDL_DestroyTexture(texture);
		}
		SDL_FreeSurface(surface);
	}
}

void drawThickRect(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a, int width) {
	thickLineRGBA(renderer, x1, y1, x2, y1, width, r, g, b, a);
	thickLineRGBA(renderer, x2, y1, x2, y2, width, r, g, b, a);
	thickLineRGBA(renderer, x2, y2, x1, y2, width, r, g, b, a);
	thickLineRGBA(renderer, x1, y2, x1, y1, width, r, g, b, a);
}

void drawEllipse(SDL_Renderer* renderer, int x0, int y0, int radiusX, int radiusY)
{
    int accuracy = 1000;
    SDL_Point points[1000];
    for (int i = 0; i < accuracy; i++)
    {
        points[i].x = x0 + radiusX * cos((2 * i * M_PI) / accuracy);
        points[i].y = y0 + radiusY * sin((2 * i * M_PI) / accuracy);
    }

    SDL_RenderDrawLines(renderer, points, accuracy);
}

void drawThickEllipse(SDL_Renderer* renderer, int x0, int y0, int radiusX, int radiusY, int w)
{
    for (int i = 0; i < w; i++)
    {
        drawEllipse(renderer, x0, y0, radiusX - i, radiusY - i);
    }
}

void drawMenu(SDL_Renderer* renderer, Menu* menu, TTF_Font* font) {
	SDL_Color white = { 255, 255, 255,255 };
	//tools
	for (int i = 0; i < menu->toolsCounter; i++) {
		if (i == menu->currentTool) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		SDL_RenderDrawRect(renderer, &(menu->tools[i].rect));

		drawText(renderer, font, menu->tools[i].text, menu->tools[i].rect.x + 5, menu->tools[i].rect.y, white);
	}


	//colors
	for (int i = 0; i < menu->colorsCounter; i++) {
		if (i == menu->currentColor) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		SDL_RenderDrawRect(renderer, &(menu->colors[i].rect));

		drawText(renderer, font, menu->colors[i].text, menu->colors[i].rect.x + 5, menu->colors[i].rect.y, white);
	}


	//widths
	for (int i = 0; i < menu->widthsCounter; i++) {
		if (i == menu->currentWidth) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		SDL_RenderDrawRect(renderer, &(menu->widths[i].rect));

		drawText(renderer, font, menu->widths[i].text, menu->widths[i].rect.x + 5, menu->widths[i].rect.y, white);
	}


	//generals
	for (int i = 0; i < menu->generalsCounter; i++) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &(menu->generals[i].rect));

		drawText(renderer, font, menu->generals[i].text, menu->generals[i].rect.x + 5, menu->generals[i].rect.y, white);
	}


	//saves
	for (int i = 0; i < menu->savesCounter; i++) {
		if (i < menu->lastSaved) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		SDL_RenderDrawRect(renderer, &(menu->saves[i].rect));

		drawText(renderer, font, menu->saves[i].text, menu->saves[i].rect.x + 5, menu->saves[i].rect.y, white);
	}
}