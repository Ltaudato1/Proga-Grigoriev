#include <Windows.h>
#include <math.h>
#include "geometry.h"
#include "painter.h"
#include "calculation.h"

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

TRIANGLE iterations[11][59049];
int proceessedIterations = 0;
int currentIteration = -1;

POINT getMiddlePoint(POINT p1, POINT p2) {
    POINT mid = {
        (p1.x + p2.x) / 2,
        (p1.y + p2.y) / 2
    };

    return mid;
}

POINT calcFirstIteration(HWND hwnd, POINT p1, POINT p2) {
    POINT p3 = {
        (p2.x - p1.x) * cos(PI / 3) - (p2.y - p1.y) * sin(PI / 3) + p1.x,
        (p2.x - p1.x) * sin(PI / 3) + (p2.y - p1.y) * cos(PI / 3) + p1.y
    };
    TRIANGLE triangle = { p1, p2, p3 };
    iterations[0][0] = triangle;
    currentIteration = 0;

    drawTriangle(GetDC(hwnd), triangle);
    return p3;
}

void proceedIteration(int iteration) {
    for (int i = 0; i < pow(3, iteration - 1); ++i) {

        TRIANGLE triangle1 = {
            getMiddlePoint(iterations[iteration - 1][i].p2, iterations[iteration - 1][i].p1),
            iterations[iteration - 1][i].p2,
            getMiddlePoint(iterations[iteration - 1][i].p2, iterations[iteration - 1][i].p3),
        };

        TRIANGLE triangle2 = {
            iterations[iteration - 1][i].p1,
            getMiddlePoint(iterations[iteration - 1][i].p2, iterations[iteration - 1][i].p1),
            getMiddlePoint(iterations[iteration - 1][i].p1, iterations[iteration - 1][i].p3),
        };

        TRIANGLE triangle3 = {
            getMiddlePoint(iterations[iteration - 1][i].p1, iterations[iteration - 1][i].p3),
            getMiddlePoint(iterations[iteration - 1][i].p2, iterations[iteration - 1][i].p3),
            iterations[iteration - 1][i].p3
        };

        iterations[iteration][3 * i] = triangle1;
        iterations[iteration][3 * i + 1] = triangle2;
        iterations[iteration][3 * i + 2] = triangle3;
    }
}

TRIANGLE getIteration(int i, int j) {
    return iterations[i][j];
}

void handleIteration(HWND hwnd, iterationType type) {
    switch (type) {
    case PLUS: {
        if (currentIteration <= 9 && currentIteration != -1) {
            currentIteration++;
            if (currentIteration > proceessedIterations) {
                proceedIteration(currentIteration);
                proceessedIterations++;
            }
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    }
    case MINUS:
        if (currentIteration > 0) {
            --currentIteration;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    }
}

void handle(HDC hdc) {
    if (currentIteration != -1) {
        drawIteration(hdc, currentIteration);
    }
}