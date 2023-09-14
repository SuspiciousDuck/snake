#pragma once
#include <deque>
#include <vector>
#include "RenderWindow.hpp"
#include "Snake.hpp"

class Apples {
    public:
    Apples(int appleamount, int w_width, int w_height, int scale);
    void gen(std::deque<SDL_Rect> segments);
    void draw(RenderWindow window);
    bool collision(Snake &snake);
    private:
    std::vector<int> RandPos(std::deque<SDL_Rect> segments);
    std::vector<SDL_Rect> apples;
    std::vector<int> Color;
    int applecount;
    int w_width, w_height;
    int scale;

};