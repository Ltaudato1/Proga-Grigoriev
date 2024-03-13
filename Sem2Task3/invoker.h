#pragma once
#ifndef INVOKER_H
#define INVOKER_H

#include <Windows.h>
#include "structs.h"

void init(const char* fileName, HINSTANCE hInstance, int nCmdShow);
void open();
void close();
void paint(HINSTANCE hInctance, int nCmdShow);
void update();
void handleClick(Click click, HWND hwnd);

#endif