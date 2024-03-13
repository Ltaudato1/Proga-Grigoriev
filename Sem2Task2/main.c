#include <windows.h>
#include <math.h>
#include "geometry.h"
#include "painter.h"
#include "calculation.h"

POINT startPoint = { -1, -1 };

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_PAINT: {
        if (startPoint.x != -1 && startPoint.y != -1) {
            // Если начальная точка установлена, рисуем резиновую нить
            drawRubberBand(hwnd, startPoint);
        }
        else {
            handle(GetDC(hwnd));
        }

        break;
    }
    case WM_LBUTTONDOWN: {
        // При клике левой кнопкой мыши устанавливаем начальную точку
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    }
    case WM_LBUTTONUP: {
        // При отпускании левой кнопки мыши рисуем треугольник и сбрасываем начальную точку
        if (startPoint.x != -1 && startPoint.y != -1) {
            POINT secondPoint = { LOWORD(lParam), HIWORD(lParam) };
            calcFirstIteration(hwnd, startPoint, secondPoint);
            startPoint.x = -1;
            startPoint.y = -1;

        }
        break;
    }
    case WM_MOUSEMOVE: {
        if ((wParam & MK_LBUTTON) && startPoint.x != -1 && startPoint.y != -1) {
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    }
    case WM_KEYDOWN: {
        switch (wParam) {
        case VK_RIGHT: {
            handleIteration(hwnd, PLUS);
            break;
        }
        case VK_LEFT: {
            handleIteration(hwnd, MINUS);
            break;
        }
        case VK_ESCAPE: {
            PostQuitMessage(0);
            break;
        }
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));;
    wc.lpszClassName = L"SierpinskiTriangle";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        L"SierpinskiTriangle", L"Sierpinski Triangle",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
