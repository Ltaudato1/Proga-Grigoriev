#pragma once
#ifndef GENERAL_H
#define GENERAL_H

#include <SDL.h>

#define SCREEN_WIDTH 1300
#define SCREEN_HEIGHT 700
#define EDGE 100
typedef enum {
    PEN, ERASER, LINE, RECT, ELLIPS
} Tool;

typedef enum {
    RED, GREEN, BLUE, BLACK
} Color;

typedef enum {
    ONEPIX, THREEPIX, FIVEPIX
} Width;

typedef enum {
    NEW, SAVE
} General;

typedef enum {
    TOOL, COLOR, WIDTH, GENERAL, SAVES
} Type;

typedef struct {
    Type type;
    int num;
} Inf;



typedef struct {
    SDL_Rect rect;
    char* text;
    Tool tool;
} ToolButton;

typedef struct {
    SDL_Rect rect;
    char* text;
    Color color;
} ColorButton;

typedef struct {
    SDL_Rect rect;
    char* text;
    Width width;
} WidthButton;

typedef struct {
    SDL_Rect rect;
    char* text;
    General general;
} GeneralButton;

typedef struct {
    SDL_Rect rect;
    char* text;
    int num;
} SaveButton;

typedef struct {
    int toolsCounter;
    ToolButton* tools;

    int colorsCounter;
    ColorButton* colors;

    int widthsCounter;
    WidthButton* widths;

    int generalsCounter;
    GeneralButton* generals;

    int savesCounter;
    SaveButton* saves;

    Tool currentTool;
    Color currentColor;
    Width currentWidth;

    int lastSaved;
} Menu;

#endif
