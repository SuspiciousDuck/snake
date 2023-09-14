#include <SDL2/SDL.h>
#include <algorithm>
#include <ctime>
#include <deque>
#include <vector>
#include "Apples.hpp"
#include "RenderWindow.hpp"
#include "Snake.hpp"

std::vector<int> Apples::RandPos(std::deque<SDL_Rect> segments) {
    int x = rand() % (w_width-scale);
    while (x % scale != 0) { x = rand() % (w_width-scale); }
    int y = rand() % (w_width-scale);
    while (y % scale != 0) { y = rand() % (w_width-scale); }
    SDL_Rect temp = {x,y,scale,scale};
    for (auto& segment: segments) {
        if (SDL_HasIntersection(&temp, &segment)) { std::vector<int> recursive = RandPos(segments);
            x = recursive[0];
            y = recursive[1];
        }}
    return std::vector<int> {x, y};
}

Apples::Apples(int appleamount, int W_width, int W_height, int Scale) {
    applecount = appleamount;
    apples = {};
    w_width = W_width;
    w_height = W_height;
    scale = Scale;
    Color = {255,0,0,255};
    srand(time(0));
}

void Apples::gen(std::deque<SDL_Rect> segments) {
    while (applecount > (signed)apples.size()) {
        std::vector<int> Pos = RandPos(segments);
        apples.push_back(SDL_Rect{Pos[0],Pos[1],scale,scale});
    }
}

void Apples::draw(RenderWindow window) {
    for (auto& apple: apples) {
        window.draw(apple,Color);
    };
}

bool Apples::collision(Snake &snake) { bool result = false; std::deque<SDL_Rect> segments = snake.getSegments();
    for (auto& apple: apples) {
        for (auto& segment: segments) {
            if (SDL_HasIntersection(&apple, &segment)) result = true;
            if (result) apple.x = -scale;
        }
    }
    apples.erase(std::remove_if(apples.begin(), apples.end(), [&](auto& apple) { return apple.x == -scale; }), apples.end());
    gen(segments);
    if (result) snake.grow();
    return result;
}