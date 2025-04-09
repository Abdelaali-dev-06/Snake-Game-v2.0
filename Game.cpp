// Game.cpp
#include "Game.h"
#include <fstream>
#include <algorithm>
#include <ctime>

Game::Game()
    : window(sf::VideoMode(GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE), "Snake Game"),
      score(0), timer(0), delay(0.2f), isGameOver(false) {
    srand(static_cast<unsigned>(time(0)));

    tSnake.loadFromFile("images/blue.png");
    tFood.loadFromFile("images/red.png");
    tObstacle.loadFromFile("images/black.png");

    snakeSprite.setTexture(tSnake);
    foodSprite.setTexture(tFood);
    obstacleSprite.setTexture(tObstacle);

    font.loadFromFile("Font/PlayfairDisplay-VariableFont_wght.ttf");

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Black);
    gameOverText.setString("GAME OVER!");
    gameOverText.setPosition(GRID_WIDTH * CELL_SIZE / 2 - 100, 20);

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(5, 5);

    highScoresText.setFont(font);
    highScoresText.setCharacterSize(20);
    highScoresText.setFillColor(sf::Color::Black);
    highScoresText.setPosition(GRID_WIDTH * CELL_SIZE / 2 - 100, 70);

    resetFoodAndObstacles();
    loadHighScores();
}

Game::~Game() {}

void Game::resetFoodAndObstacles() {
    food.x = rand() % GRID_WIDTH;
    food.y = rand() % GRID_HEIGHT;

    obstacles.clear();
    for (int i = 0; i < 2; ++i) {
        Obstacle obs;
        do {
            obs.x = rand() % GRID_WIDTH;
            obs.y = rand() % GRID_HEIGHT;
        } while ((obs.x == food.x && obs.y == food.y));
        obstacles.push_back(obs);
    }
}

void Game::loadHighScores() {
    std::ifstream file(SCORE_FILE);
    int val;
    while (file >> val) {
        highScores.push_back(val);
    }
}

void Game::saveHighScores() {
    std::ofstream file(SCORE_FILE);
    for (int i = 0; i < std::min(5, (int)highScores.size()); i++) {
        file << highScores[i] << std::endl;
    }
}

void Game::processEvents() {
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            window.close();
    }

    if (!isGameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.getDirection() != 0) snake.setDirection(1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.getDirection() != 1) snake.setDirection(0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.getDirection() != 3) snake.setDirection(2);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.getDirection() != 2) snake.setDirection(3);
    }
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        timer += dt;

        processEvents();

        if (!isGameOver && timer > delay) {
            timer = 0;
            if (!snake.update(food, obstacles, score)) {
                isGameOver = true;
                highScores.push_back(score);
                std::sort(highScores.begin(), highScores.end(), std::greater<int>());
                if (highScores.size() > 5) highScores.resize(5);
                saveHighScores();
            } else if (snake.ateFood()) {
                resetFoodAndObstacles();
            }
        }

        render();
    }
}

void Game::render() {
    window.clear(isGameOver ? sf::Color::White : sf::Color(120, 200, 10));

    if (!isGameOver) {
        for (auto& obs : obstacles) {
            obstacleSprite.setPosition(obs.x * CELL_SIZE, obs.y * CELL_SIZE);
            window.draw(obstacleSprite);
        }

        for (auto& segment : snake.getSegments()) {
            snakeSprite.setPosition(segment.x * CELL_SIZE, segment.y * CELL_SIZE);
            window.draw(snakeSprite);
        }

        foodSprite.setPosition(food.x * CELL_SIZE, food.y * CELL_SIZE);
        window.draw(foodSprite);

        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
    } else {
        window.draw(gameOverText);
        std::string hs = "Score: " + std::to_string(score) + "\nTop 5 Scores:\n";
        for (int i = 0; i < std::min(5, (int)highScores.size()); i++) {
            hs += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";
        }
        highScoresText.setString(hs);
        window.draw(highScoresText);
    }

    window.display();
}
