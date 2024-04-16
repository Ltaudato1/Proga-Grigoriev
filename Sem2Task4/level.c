#include "general.h"
#include "player.h"
#include <stdio.h>
#include <SDL.h>

#define BLOCKS_ON_ROW 5
#define LEVELS 3

Level levels[LEVELS];
int currentLevel = 0;

void initLevel() {
	currentLevel++;
	levels[currentLevel - 1].numBlocks = BLOCKS_ON_ROW * currentLevel;
	levels[currentLevel - 1].numActive = levels[currentLevel - 1].numBlocks;
	levels[currentLevel - 1].blocks = (Block*)malloc(sizeof(Block) * levels[currentLevel - 1].numBlocks);

	for (int i = 0; i < currentLevel; ++i) {
		for (int j = 0; j < BLOCKS_ON_ROW; ++j) {
			levels[currentLevel - 1].blocks[i * BLOCKS_ON_ROW + j].position.x = 0.15 * SCREEN_WIDTH + j * 0.15 * SCREEN_WIDTH;
			levels[currentLevel - 1].blocks[i * BLOCKS_ON_ROW + j].position.y = 0.15 * SCREEN_HEIGHT + i * 0.125 * SCREEN_HEIGHT;

			levels[currentLevel - 1].blocks[i * BLOCKS_ON_ROW + j].width = SCREEN_WIDTH * 0.1;
			levels[currentLevel - 1].blocks[i * BLOCKS_ON_ROW + j].height = SCREEN_HEIGHT * 0.1;

			levels[currentLevel - 1].blocks[i * BLOCKS_ON_ROW + j].strength = i + 1;
			levels[currentLevel - 1].blocks[i * BLOCKS_ON_ROW + j].active = true;
		}
	}
}

void redrawLevel(SDL_Renderer* renderer) {
	for (int i = 0; i < levels[currentLevel - 1].numBlocks; ++i) {
		if (!levels[currentLevel - 1].blocks[i].active) continue;

		SDL_Rect rect =
		{   levels[currentLevel - 1].blocks[i].position.x,
			levels[currentLevel - 1].blocks[i].position.y,
			levels[currentLevel - 1].blocks[i].width,
			levels[currentLevel - 1].blocks[i].height
		};

		SDL_SetRenderDrawColor
		(
			renderer,
			100 * (LEVELS - levels[currentLevel - 1].blocks[i].strength + 1),
			100 * (LEVELS - levels[currentLevel - 1].blocks[i].strength + 1),
			100 * (LEVELS - levels[currentLevel - 1].blocks[i].strength + 1),
			0
		);  // Color
		SDL_RenderFillRect(renderer, &rect);
	}
	checkCollisionsWithBricks(levels[currentLevel - 1].blocks, levels[currentLevel - 1].numBlocks);
}

void killBlock(Block* block) {
	block->active = false;
	levels[currentLevel - 1].numActive--;
	if (levels[currentLevel - 1].numActive == 0) {
		initLevel();
		unlaunchBall();
	}
}