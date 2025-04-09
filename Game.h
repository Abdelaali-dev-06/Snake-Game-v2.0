// Game.h
#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void render();
    void resetFoodAndObstacles();
    void loadHighScores();
    void saveHighScores();

    sf::RenderWindow window;
    sf::Texture tSnake, tFood, tObstacle;
    sf::Sprite snakeSprite, foodSprite, obstacleSprite;
    sf::Font font;
    sf::Text gameOverText, scoreText, highScoresText;

    Snake snake;
    Food food;
    std::vector<Obstacle> obstacles;

    int score;
    float timer, delay;
    bool isGameOver;

    std::vector<int> highScores;
    const std::string SCORE_FILE = "scores_file.txt";
};
