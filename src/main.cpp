#include <SDL2/SDL.h>
#include <iostream>
#include "RenderWindow.hpp"
#include "Clock.hpp"
#include "Apples.hpp"
#include "Snake.hpp"
#include "Controller.hpp"

#define W_WIDTH 400
#define W_HEIGHT 400
#define SCALE 20
#define APPLEAMOUNT 1
#define SPEEDFACTOR 8
#define FPS 15

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_INIT failed to initialize SDL_INIT_VIDEO: %s\n", SDL_GetError());
        return 1;
    }
    RenderWindow window("Snake Game",W_WIDTH,W_HEIGHT);
    Controller controller;
    Clock clock;
    Apples apples(APPLEAMOUNT, W_WIDTH, W_HEIGHT, SCALE);
    Snake snake(W_WIDTH, W_HEIGHT, SCALE);
    apples.gen(snake.getSegments());
    double elapsed = 0;

    while (window.status()) {
        controller.HandleEvents(window, snake);
        double delta = clock.tick();
        elapsed += delta;
        if (elapsed > 1.0/FPS) {
            elapsed -= 1.0/FPS;
            window.clear();
            
            apples.collision(snake);
            apples.draw(window);
            
            snake.logic();
            snake.draw(window);

            window.display();
        } else SDL_Delay(1);
    }
    window.cleanup();
}