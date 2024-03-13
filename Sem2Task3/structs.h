#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H

#include <Windows.h>

typedef struct {
    int red;
    int green;
    int blue;
} Color;

typedef struct {
    POINT position;
    Color color;
    int id;
    HWND hwnd;
} Window;

typedef struct {
    POINT position;
    Color color;
    Color highlightColor;
    int windowId;
    char name[255];
    HWND hwnd;
} Button;

typedef struct {
    int buttonsCounter;
    int windowsCounter;
    Window* windows;
    Button* buttons;
    int currentButton;
} Menu;

typedef enum {
    UP, DOWN, ENTER
} Click;
#endif