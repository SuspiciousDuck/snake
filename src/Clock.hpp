#pragma once
#include <SDL2/SDL.h>

class Clock {
    public:
    Clock();
    double tick();
    private:
    Uint64 curr;
    Uint64 last;
};