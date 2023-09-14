#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>
#include "RenderWindow.hpp"
#include "Snake.hpp"

class Controller {
    public:
    Controller();
    void HandleEvents(RenderWindow &window, Snake &snake);
    private:
    std::vector<std::string> queue;
    std::map<std::string, Snake::Direction> movement;
    Snake::Direction lastDir;
    SDL_Event event;
};