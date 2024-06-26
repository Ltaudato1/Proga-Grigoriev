#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "general.h"
#include "level.h"
#include "bonus.h"
#include "player.h"
#include <stdbool.h>
#include <stdlib.h>

#define PADDLE_SPEED 450

Paddle paddle;
Ball ball;
bool launched = false;
SDL_Texture* heartTexture;

void initIcon(SDL_Renderer* renderer) {
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }

    SDL_Surface* loadedSurface = IMG_Load("heart.png");
    if (loadedSurface == NULL) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        return;
    }

    heartTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (heartTexture == NULL) {
        printf("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
        return;
    }

    SDL_FreeSurface(loadedSurface);
}

void initPaddle(float x, float y, float width, float height) {
    paddle.position.x = x;
    paddle.position.y = y;
    paddle.width = width;
    paddle.height = height;
    paddle.hp = 2;
}

void movePaddle(Direction direction) {
    switch (direction) {
    case LEFT:
        if (paddle.position.x > paddle.speed) {
            paddle.speed = -PADDLE_SPEED;
        }
        break;
    case RIGHT:
        if (paddle.position.x < SCREEN_WIDTH - paddle.speed - paddle.width) {
            paddle.speed = PADDLE_SPEED;
        }
        break;
    }
}

void drawPaddle(SDL_Renderer* renderer) {
    SDL_Rect paddleRect = { paddle.position.x, paddle.position.y, paddle.width, paddle.height };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Color
    SDL_RenderFillRect(renderer, &paddleRect);             // Render paddle
}

void stopPaddle() {
    paddle.speed = 0;
}

void initBonus(Bonus* bonus) {
    switch (bonus->type) {
    case EXTRA_LIFE:
        paddle.hp++;
        break;
    case PADDLE_PLUS_WIDTH:
        paddle.position.x -= 50;
        paddle.width += 100;
    }
    killBonus();
}

void bonusCheckCollision(Bonus* bonus) {
    if (bonus->position.x + bonus->width <= paddle.position.x + paddle.width
        && bonus->position.x >= paddle.position.x
        && bonus->position.y + bonus->height > paddle.position.y) {
        initBonus(bonus);
    }
    else if (bonus->position.y + bonus->height > SCREEN_HEIGHT) {
        killBonus();
    }
}




void initBall(float radius, float velocityX, float velocityY) {
    ball.radius = radius;
    ball.currentPosition.x = paddle.position.x + paddle.width / 2;
    ball.currentPosition.y = paddle.position.y - ball.radius - 10;
    ball.velocity.x = velocityX;
    ball.velocity.y = velocityY;
}

void launchBall() {
    launched = true;
}

void unlaunchBall() {
    launched = false;
    ball.velocity.x = -300;
    ball.velocity.y = -300;
}

void updatePlayer(float deltaTime) {
    if (paddle.position.x <= 0 && paddle.speed < 0) paddle.speed = 0;
    if (paddle.position.x + paddle.width >= SCREEN_WIDTH && paddle.speed > 0) paddle.speed = 0;

    paddle.position.x += paddle.speed * deltaTime;

    if (launched) {
        ball.currentPosition.x += ball.velocity.x * deltaTime;
        ball.currentPosition.y += ball.velocity.y * deltaTime;

        // Check collision with paddle
        if (ball.currentPosition.x <= paddle.position.x + paddle.width 
            && ball.currentPosition.x > paddle.position.x 
            && ball.currentPosition.y > paddle.position.y) {
            ball.velocity.y *= -1;
            ball.currentPosition.y -= 5;
        }

        // Check collision with borders
        else if (ball.currentPosition.y < ball.radius) {
            ball.velocity.y *= -1;
            ball.currentPosition.y += 5;
        }

        else if (ball.currentPosition.x < ball.radius) {
            ball.velocity.x *= -1;
            ball.currentPosition.x += 5;
        }

        else if (ball.currentPosition.x > SCREEN_WIDTH - ball.radius) {
            ball.velocity.x *= -1;
            ball.currentPosition.x -= 5;
        }

        else if (ball.currentPosition.y > SCREEN_HEIGHT - ball.radius) {
            unlaunchBall();
            paddle.hp--;
        }
    }
    else {
        ball.currentPosition.x = paddle.position.x + paddle.width / 2;
        ball.currentPosition.y = paddle.position.y - ball.radius - 5;
    }
}

void drawBall(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int x = ball.currentPosition.x - ball.radius; x <= ball.currentPosition.x + ball.radius; x++) {
        for (int y = ball.currentPosition.y - ball.radius; y <= ball.currentPosition.y + ball.radius; y++) {
            if ((x - ball.currentPosition.x) * (x - ball.currentPosition.x) + (y - ball.currentPosition.y) * (y - ball.currentPosition.y) <= ball.radius * ball.radius) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void checkCollisionsWithBricks(Block* blocks, int num) {
    for (int i = 0; i < num; ++i) {
        if (!blocks[i].active) continue;

        // Check by vertical
        if (ball.currentPosition.x >= blocks[i].position.x 
            && ball.currentPosition.x <= blocks[i].position.x + blocks[i].width
            && ball.currentPosition.y - ball.radius <= blocks[i].position.y + blocks[i].height
            && ball.currentPosition.y - ball.radius >= blocks[i].position.y) {
            ball.velocity.y *= -1;
            ball.currentPosition.y += 5;
            blocks[i].strength--;
        }

        else if (ball.currentPosition.x >= blocks[i].position.x
            && ball.currentPosition.x <= blocks[i].position.x + blocks[i].width
            && ball.currentPosition.y + ball.radius >= blocks[i].position.y
            && ball.currentPosition.y + ball.radius <= blocks[i].position.y + blocks[i].height) {
            ball.velocity.y *= -1;
            ball.currentPosition.y -= 5;
            blocks[i].strength--;
        }

        // Check by horizontal
        else if (ball.currentPosition.y >= blocks[i].position.y
            && ball.currentPosition.y <= blocks[i].position.y + blocks[i].height
            && ball.currentPosition.x - ball.radius <= blocks[i].position.x + blocks[i].width
            && ball.currentPosition.x - ball.radius >= blocks[i].position.x) {
            ball.velocity.x *= -1;
            ball.currentPosition.x += 5;
            blocks[i].strength--;
        }

        else if (ball.currentPosition.y >= blocks[i].position.y
            && ball.currentPosition.y <= blocks[i].position.y + blocks[i].height
            && ball.currentPosition.x + ball.radius >= blocks[i].position.x
            && ball.currentPosition.x + ball.radius <= blocks[i].position.x + blocks[i].width) {
            ball.velocity.x *= -1;
            ball.currentPosition.x += 5;
            blocks[i].strength--;
        }
        
        if (blocks[i].strength == 0) {
            killBlock(&blocks[i]);
            if (rand() % 20 < 5) {
                dropBonus(blocks[i].position.x + blocks[i].width / 2, blocks[i].position.y + blocks[i].height / 2);
            }
        }
    }
}

void drawLives(SDL_Renderer* renderer) {
    for (int i = 0; i < paddle.hp; ++i) {
        SDL_Rect destRect = { 20 + i * 30, 20, 30, 30 };
        SDL_RenderCopy(renderer, heartTexture, NULL, &destRect);
    }
}

bool checkHp() {
    return (paddle.hp != 0);
}