#include <SDL2/SDL.h>
#include <iostream>
#include <algorithm>
#include <map>
#include "Controller.hpp"
#include "Snake.hpp"
#include "RenderWindow.hpp"

bool exists(std::map<std::string,Snake::Direction> map, std::string m) { return map.find(m) != map.end(); }
void v_erase(std::vector<std::string> v, std::string m) { v.erase(std::remove(v.begin(), v.end(), m)); }
bool isOpposite(Snake::Direction newDir, Snake::Direction lastDir) {
    if (lastDir == Snake::Direction::Up and newDir == Snake::Direction::Down or lastDir == Snake::Direction::Down and newDir == Snake::Direction::Up) return true;
    if (lastDir == Snake::Direction::Left and newDir == Snake::Direction::Right or lastDir == Snake::Direction::Right and newDir == Snake::Direction::Left) return true;
    return false;
}

Controller::Controller() {
    queue = {};
    movement = {{"Up", Snake::Direction::Up},
                {"Down", Snake::Direction::Down},
                {"Left", Snake::Direction::Left},
                {"Right", Snake::Direction::Right}};
    lastDir = Snake::Direction::None;
}

void Controller::HandleEvents(RenderWindow &window, Snake &snake) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) window.close();
        if (event.type == SDL_KEYDOWN or event.type == SDL_KEYUP) {
            bool IsRelease = event.key.type == SDL_KEYUP;
            SDL_Keycode key = event.key.keysym.sym;
            std::string keystr = SDL_GetScancodeName(event.key.keysym.scancode);

            if (!IsRelease and exists(movement, keystr)) { queue.push_back(keystr); }
            else { v_erase(queue, keystr); }
            
            if (!queue.empty()) { const std::string b = queue.back();
                const Snake::Direction newDir = movement[b];
                if (!isOpposite(newDir, lastDir)) snake.upd_dir(newDir);
                std::cout << b << "\n";
            }
        }
    }
}