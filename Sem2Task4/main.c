#include <SDL.h>
#include <stdio.h>

int main() {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    int quit = 0;

    // ������������� SDL
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // �������� ����
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // ������� ������
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // ��������� ��������

        // ���������� ������
        SDL_RenderPresent(renderer);
    }

    // ������������ �������� � �������� SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
