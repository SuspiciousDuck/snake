#pragma once
#include <SDL2/SDL.h>
#include <vector>

class RenderWindow {
    public:
    RenderWindow(const char* w_title,int W_WIDTH, int W_HEIGHT);
    void draw(SDL_Rect Rect,std::vector<int> Color);
    void display();
    void cleanup();
    void clear();
    void close();
    const bool status();
    private:
    bool MaintainWindow;
    SDL_Window* window;
    SDL_Renderer* renderer;
};