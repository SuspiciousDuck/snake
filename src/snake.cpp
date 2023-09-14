#include <algorithm>
#include <iostream>
#include "RenderWindow.hpp"
#include "Snake.hpp"

int Snake::toGrid(int pos) { int result = pos;
    int remainder = pos%scale;
    if (remainder == 0) return result;
    if (remainder >= scale/2) { result += remainder; }
    if (remainder < scale/2) { result -= remainder; }
    return result;
}

Snake::Snake(int w_width, int w_height, int Scale) {
    w_w = w_width; w_h = w_height;
    scale = Scale;
    segments = {}; inputQueue = {};
    color = {0,255,0,255};
    velx = 0; vely = 0;
    head = {w_w/10, w_h/10, scale, scale};
    segments.push_front(head);
    size = 1;
    direction = Direction::None;
}

void Snake::draw(RenderWindow & window) {
    for (auto& segment: segments) {
        window.draw(segment, color);
    }
}

void Snake::logic() {
    // Movement
    if (direction == Direction::Up) head.y -= scale;
    if (direction == Direction::Down) head.y += scale;
    if (direction == Direction::Left) head.x -= scale;
    if (direction == Direction::Right) head.x += scale;

    // Segments
    for (auto& segment: segments) {
        if (SDL_HasIntersection(&segment, &head) and !SDL_HasIntersection(&segment, &segments[0])) { size = 1; break; }
    }
    if (!SDL_HasIntersection(&head, &segments[0])) segments.push_front(head);
    while ((signed)segments.size() > size and !growing) segments.pop_back();
    if (growing) { growing = false; ++size; }
    
    // Out of Bounds
    if (head.x < 0) { head.x = w_w-scale; }
    if (head.x > w_w-scale) { head.x = 0; }
    if (head.y < 0) { head.y = w_h-scale; }
    if (head.y > w_h-scale) { head.y = 0; }
}

void Snake::upd_dir(Direction dir) { direction = dir; }

bool locate(std::deque<SDL_Rect> d, int x, int y) { bool result = false;
    for (auto& rect: d) {
        if (rect.x == x and rect.y == y) { result = true; break; }
    } return result;
}

void Snake::grow() { growing = true; }

std::deque<SDL_Rect> Snake::getSegments() { return segments; }