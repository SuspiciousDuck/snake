#include <SDL2/SDL.h>
#include <iostream>
#include <algorithm>
#include <map>
#include "Controller.hpp"
#include "Snake.hpp"
#include "RenderWindow.hpp"

bool m_exists(std::map<std::string,Snake::Direction> map, std::string m) { return map.find(m) != map.end(); }
bool v_exists(std::vector<std::string> v, std::string m) { return std::find(v.begin(), v.end(), m) != v.end(); }
void v_erase(std::vector<std::string> &v, std::string m) { v.erase(std::remove(v.begin(), v.end(), m), v.end()); }
bool Controller::isOpposite(std::string newDir) {
    if ((lastDir == "Up" and newDir == "Down") or (lastDir == "Down" and newDir == "Up")) return true;
    if ((lastDir == "Left" and newDir == "Right") or (lastDir == "Right" and newDir == "Left")) return true;
    return false;
}

Controller::Controller() {
    queue = {};
    movement = {{"Up", Snake::Direction::Up},
                {"Down", Snake::Direction::Down},
                {"Left", Snake::Direction::Left},
                {"Right", Snake::Direction::Right}};
    lastDir = "None";
}

void Controller::HandleEvents(RenderWindow &window, Snake &snake) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) window.close();
        if (event.type == SDL_KEYDOWN or event.type == SDL_KEYUP) {
            bool IsRelease = event.key.type == SDL_KEYUP;
            std::string keystr = SDL_GetScancodeName(event.key.keysym.scancode);

            if (!IsRelease and m_exists(movement, keystr) and !v_exists(queue, keystr)) { queue.push_back(keystr); }
            else if (IsRelease and v_exists(queue, keystr)) { v_erase(queue, keystr); }
            
            if (!queue.empty()) { std::string b = queue.back();
                if (!isOpposite(b)) { snake.upd_dir(movement[b]); lastDir = b; }
                for (auto& key: queue) { std::cout << key << ", "; }
                std::cout << "\n";
            }
        }
    }
}