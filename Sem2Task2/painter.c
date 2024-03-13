#include <Windows.h>
#include <math.h>
#include "geometry.h"
#include "calculation.h"

void drawTriangle(HDC hdc, TRIANGLE triangle) {
    POINT points[3];
    points[0] = triangle.p1;
    points[1] = triangle.p2;
    points[2] = triangle.p3;
    Polygon(hdc, points, 3);
}

void drawRubberBand(HWND hwnd, POINT p1) {
    POINT p2;
    GetCursorPos(&p2);
    ScreenToClient(hwnd, &p2);

    POINT p3;
    p3 = calcFirstIteration(hwnd, p1, p2);

    TRIANGLE triangle = { p1, p2, p3 };

    HDC hdc = GetDC(hwnd);
    
    drawTriangle(hdc, triangle);
    
    ReleaseDC(hwnd, hdc);
}

void drawIteration(HDC hdc, int it) {
    for (int i = 0; i < pow(3, it); ++i) {
        TRIANGLE currentTriangle = getIteration(it, i);
        drawTriangle(hdc, currentTriangle);
    }
}