#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "invoker.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT:
        update();
        break;
    case WM_KEYDOWN:
        switch (wParam) {
        case VK_DOWN:
            handleClick(DOWN, hwnd);
            break;
        case VK_UP:
            handleClick(UP, hwnd);
            break;
        case VK_RETURN:
            handleClick(ENTER, hwnd);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(WHITE_BRUSH);
    wc.lpszClassName = L"UI";

    RegisterClass(&wc);

    open();
    init("menu.txt", hInstance, nCmdShow);

    paint(hInstance, nCmdShow);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    close();
    return 0;
} 