#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "general.h"
#include "level.h"
#include "bonus.h"
#include <stdio.h>
#include <SDL.h>

typedef enum {
    LEFT, RIGHT
} Direction;

typedef struct {
    Vector2D position;
    float width;
    float height;
    float speed;
    int hp;
} Paddle;

typedef struct {
    Vector2D currentPosition;
    Vector2D velocity;
    float radius;
} Ball;


void drawPaddle(SDL_Renderer* renderer);
void movePaddle(Direction direction);
void initPaddle(float x, float y, float width, float height);
void initBall(float radius, float velocityX, float velocityY);
void initIcon(SDL_Renderer* renderer);
void drawLives(SDL_Renderer* renderer);
void updatePlayer(float deltaTime);
void drawBall(SDL_Renderer* renderer);
void launchBall();
void unlaunchBall();
void stopPaddle();
void checkCollisionsWithBricks(Block* block, int num);
void bonusCheckCollision(Bonus* bonus);
bool checkHp();

#endif
