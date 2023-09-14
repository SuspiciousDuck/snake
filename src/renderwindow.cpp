#include <iostream>
#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* w_title, int w_width, int w_height)
    :window(nullptr), renderer(nullptr)
{
    window = SDL_CreateWindow(w_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w_width, w_height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow failed to initialize: %s\n", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    MaintainWindow = true;
}

void RenderWindow::display() { SDL_RenderPresent(renderer); }

void RenderWindow::cleanup() { SDL_DestroyWindow(window); }

void RenderWindow::close() { MaintainWindow = false; std::cout << "a\n"; }

const bool RenderWindow::status() { return MaintainWindow; }

void RenderWindow::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void RenderWindow::draw(SDL_Rect Rect,std::vector<int> Color) {
    SDL_SetRenderDrawColor(renderer, Color[0], Color[1], Color[2], Color[3]);
    SDL_RenderFillRect(renderer, &Rect);
}