#include <Windows.h>
#include <stdlib.h>
#include "structs.h"

void redrawButton(Button* button) {
    RedrawWindow(button->hwnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
}

void drawAlign(Button* button, COLORREF color) {
    HDC hdc = GetDC(button->hwnd);

    SetTextColor(hdc, color);

    ReleaseDC(button->hwnd, hdc);
}

void drawWindow(Window* window, Button* buttons, HINSTANCE hInstance, int nCmdShow, int buttonsCounter) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(window->hwnd, &ps);
    for (int i = 0; i < buttonsCounter; ++i) {
        if (buttons[i].windowId == window->id) {
            buttons[i].hwnd = CreateWindowA(
                "BUTTON",                          // Predefined class; Unicode assumed 
                buttons[i].name,                   // Button text 
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
                buttons[i].position.x,             // x position 
                buttons[i].position.y,             // y position 
                100,                                // Button width
                100,                                // Button height
                window->hwnd,                       // Parent window
                NULL,                               // No menu.
                (HINSTANCE)GetWindowLongPtr(window->hwnd, GWLP_HINSTANCE),
                NULL
            );
        }
    }
    EndPaint(window->hwnd, &ps);
    ShowWindow(window->hwnd, nCmdShow);
}
