#include <stdio.h>
#include <SDL.h>
#include "general.h"
#include "player.h"
#include "bonus.h"
#include <stdbool.h>

bool isFalling = false;
Bonus bonus;

void dropBonus(float x, float y) {
	if (!isFalling) {
		bonus.position.x = x;
		bonus.position.y = y;
		bonus.width = 0.08 * SCREEN_WIDTH;
		bonus.height = bonus.width;
		bonus.velocityY = 400;
		isFalling = true;
		
	}
}

void redrawBonus(SDL_Renderer* renderer, float deltaTime) {
	if (isFalling) {
		bonus.position.y += bonus.velocityY * deltaTime;
		SDL_Rect rect = { bonus.position.x, bonus.position.y, bonus.width, bonus.height };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);
		bonusCheckCollision(&bonus);
	}
}

void killBonus() {
	isFalling = false;
}