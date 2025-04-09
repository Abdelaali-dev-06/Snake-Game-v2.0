// Snake.cpp
#include "Snake.h"
#include <cstdlib>

Snake::Snake() : direction(2), justAte(false) {
    segments.push_back({ GRID_WIDTH / 2, GRID_HEIGHT / 2 });
}

bool Snake::update(Food& food, const std::vector<Obstacle>& obstacles, int& score) {
    for (int i = segments.size() - 1; i > 0; --i)
        segments[i] = segments[i - 1];

    switch (direction) {
        case 0: segments[0].y += 1; break;
        case 1: segments[0].y -= 1; break;
        case 2: segments[0].x += 1; break;
        case 3: segments[0].x -= 1; break;
    }

    if (segments[0].x < 0) segments[0].x = GRID_WIDTH - 1;
    if (segments[0].x >= GRID_WIDTH) segments[0].x = 0;
    if (segments[0].y < 0) segments[0].y = GRID_HEIGHT - 1;
    if (segments[0].y >= GRID_HEIGHT) segments[0].y = 0;

    for (const auto& obs : obstacles) {
        if (segments[0].x == obs.x && segments[0].y == obs.y)
            return false;
    }

    for (int i = 1; i < segments.size(); i++) {
        if (segments[0].x == segments[i].x && segments[0].y == segments[i].y)
            return false;
    }

    justAte = false;
    if (segments[0].x == food.x && segments[0].y == food.y) {
        segments.push_back(segments.back());
        score++;
        justAte = true;
    }

    return true;
}

bool Snake::ateFood() const {
    return justAte;
}

void Snake::setDirection(int d) {
    direction = d;
}

int Snake::getDirection() const {
    return direction;
}

const std::vector<SnakeSegment>& Snake::getSegments() const {
    return segments;
}

