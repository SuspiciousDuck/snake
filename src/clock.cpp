#include <SDL2/SDL.h>
#include "Clock.hpp"

Clock::Clock() {
    curr = SDL_GetPerformanceCounter();
    last = 0;
}

double Clock::tick() {
    last = curr;
    curr = SDL_GetPerformanceCounter();

    return (double)((curr-last)/(double)SDL_GetPerformanceFrequency());
}