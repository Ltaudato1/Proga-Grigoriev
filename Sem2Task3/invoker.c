#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "painter.h"

Menu menu;

void init(const char* fileName, HINSTANCE hInstance, int nCmdShow) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return;
    }

    menu.windowsCounter = 0;
    menu.buttonsCounter = 0;

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        strtok(line, "\n");
        if (strcmp(line, "WindowBegin") == 0) {
            menu.windowsCounter++;
            Window window;
            fscanf(file, "\tPosition=(%d,%d)\n", &window.position.x, &window.position.y);
            fscanf(file, "\tColor=(%d,%d,%d)\n", &window.color.red, &window.color.green, &window.color.blue);
            fscanf(file, "\tId=%d\n", &window.id);

            menu.windows = (Window*)realloc(menu.windows, sizeof(Window) * menu.windowsCounter);
            menu.windows[menu.windowsCounter - 1] = window;
            fgets(line, sizeof(line), file);
        }
        else if (strcmp(line, "ButtonBegin") == 0) {
            menu.buttonsCounter++;
            Button button;
            fscanf(file, "\tPosition=(%d,%d)\n", &button.position.x, &button.position.y);
            fscanf(file, "\tColor=(%d,%d,%d)\n", &button.color.red, &button.color.green, &button.color.blue);
            fscanf(file, "\tHiglightColor=(%d,%d,%d)\n", &button.highlightColor.red, &button.highlightColor.green, &button.highlightColor.blue);
            fscanf(file, "\tName=%s\n", button.name);
            fscanf(file, "\tWindowId=%d\n", &button.windowId);

            menu.buttons = (Button*)realloc(menu.buttons, sizeof(Button) * menu.buttonsCounter);
            menu.buttons[menu.buttonsCounter - 1] = button;
            fgets(line, sizeof(line), file);
        }
        else if (strcmp(line, "MenuEnd") == 0) {
            fclose(file);
            return;
        }
    }
}

void open() {
    menu.buttons = (Button*)malloc(sizeof(Button));
    menu.windows = (Window*)malloc(sizeof(Window));
    menu.currentButton = -1;
}

void close() {
    free(menu.buttons);
    free(menu.windows);
}

void paint(HINSTANCE hInstance, int nCmdShow) {
    for (int i = 0; i < menu.windowsCounter; ++i) {
        menu.windows[i].hwnd = CreateWindow(
            L"UI",                     // Имя класса, зарегистрированного ранее
            L"User Interface",                    // Заголовок окна
            WS_OVERLAPPEDWINDOW,                  // Стиль окна
            menu.windows[i].position.x,           // Положение по X
            menu.windows[i].position.y,          // Положение по Y
            CW_USEDEFAULT,                                 // Ширина
            CW_USEDEFAULT,                                // Высота
            NULL,                               // Дескриптор родительского окна
            NULL,                               // Дескриптор меню
            hInstance,                          // Дескриптор экземпляра
            NULL                                // Дополнительные параметры создания
        );


        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(menu.windows[i].hwnd, &ps);
        for (int i = 0; i < menu.buttonsCounter; ++i) {
            if (menu.buttons[i].windowId == menu.windows[i].id) {
                menu.buttons[i].hwnd = CreateWindowA(
                    "Button",                          // Predefined class; Unicode assumed 
                    menu.buttons[i].name,                   // Button text 
                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
                    menu.buttons[i].position.x,             // x position 
                    menu.buttons[i].position.y,             // y position 
                    100,                                // Button width
                    100,                                // Button height
                    menu.windows[i].hwnd,                       // Parent window
                    NULL,                               // No menu.
                    (HINSTANCE)GetWindowLongPtr(menu.windows[i].hwnd, GWLP_HINSTANCE),
                    NULL
                );
            }
        }
        EndPaint(menu.windows[i].hwnd, &ps);
        ShowWindow(menu.windows[i].hwnd, nCmdShow);
    }
}

void update() {
    for (int i = 0; i < menu.buttonsCounter; ++i) {

        if (i == menu.currentButton) {
            drawAlign(
                &menu.buttons[i],
                RGB(menu.buttons[i].highlightColor.red, menu.buttons[i].highlightColor.green, menu.buttons[i].highlightColor.blue)
            );
        }
        else {
            drawAlign(&menu.buttons[i], RGB(0, 0, 0));
        }
    }
}

void handleClick(Click click, HWND hwnd) {
    switch (click) {
    case DOWN:
        menu.currentButton = (menu.currentButton + 1) % menu.buttonsCounter;
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case UP:
        menu.currentButton = (menu.currentButton - 1 + menu.buttonsCounter) % menu.buttonsCounter;
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case ENTER:
        SendMessage(menu.buttons[menu.currentButton].hwnd, BM_CLICK, 0, 0);
        break;
    }
}