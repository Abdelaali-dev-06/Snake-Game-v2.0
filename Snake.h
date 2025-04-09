// Snake.h
#pragma once
#include <vector>

const int GRID_WIDTH = 30;
const int GRID_HEIGHT = 20;
const int CELL_SIZE = 16;

struct SnakeSegment {
    int x, y;
};

struct Food {
    int x, y;
};

struct Obstacle {
    int x, y;
};

class Snake {
public:
    Snake();
    bool update(Food& food, const std::vector<Obstacle>& obstacles, int& score);
    bool ateFood() const;
    void setDirection(int d);
    int getDirection() const;
    const std::vector<SnakeSegment>& getSegments() const;

private:
    std::vector<SnakeSegment> segments;
    int direction;
    bool justAte;
};
