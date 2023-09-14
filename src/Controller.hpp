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
    bool isOpposite(std::string newDir);
    std::vector<std::string> queue;
    std::map<std::string, Snake::Direction> movement;
    std::string lastDir;
    SDL_Event event;
};