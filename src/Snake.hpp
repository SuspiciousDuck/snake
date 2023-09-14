#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <deque>
#include "RenderWindow.hpp"

class Snake {
    public:
    enum class Direction { Up, Down, Left, Right, None };
    Snake(int w_width, int w_height, int scale);
    void draw(RenderWindow & window);
    void logic();
    void grow();
    void upd_dir(Direction direction);
    std::deque<SDL_Rect> getSegments();
    private:
    int toGrid(int pos);
    std::deque<SDL_Rect> segments;
    std::deque<SDL_Rect> inputQueue;
    std::vector<int> color;
    SDL_Rect head;
    int velx,vely;
    int w_w,w_h;
    int scale;
    int size;
    bool growing;
    Direction direction;
};