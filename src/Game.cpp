#include "Game.h"
#include "Snake.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace sf;

Game::Game(Font &font) : window(VideoMode(595, 645), "Snake", Style::Titlebar | Style::Close), fruit(Vector2f(15, 15)), top_border(Vector2f(595, 3)) {
    window.setVerticalSyncEnabled(true);
    fruit.setOrigin(7.5, 7.5);
    scoreboard.setFont(font);
    scoreboard.setString("SCORE: 0");
    scoreboard.setCharacterSize(35);
    scoreboard.setPosition(10, 5);
    highscore_text.setFont(font);
    highscore_text.setCharacterSize(20);
    highscore_text.setPosition(300, 3);
    top_border.setOrigin(0, 3);
    top_border.setPosition(0, 50);


    std::ifstream file("highscore.txt");
    if (file.is_open()) {
        std::string line;
        if (getline(file, line)) {
            highscore = stoi(line);
            highscore_text.setString("HIGH SCORE: " + line);
        }
        file.close();
    } else {
        highscore = 0;
        highscore_text.setString("HIGH SCORE: 0");
    }
}

void Game::run() {
    fruit.setPosition(12 * 35 + 17.5, 8 * 35 + 67.5);
    clock.restart();
    moved = true;
    direction = "right";
    score = 0;

    const int MAX_FRAMESKIP = 5;
    const Time TIME_PER_FRAME = milliseconds(125);
    Time time_since_last_update = Time::Zero;
    while (window.isOpen()) {
        time_since_last_update += clock.restart();

        int loop_count = 0;
        while (time_since_last_update > TIME_PER_FRAME && loop_count < MAX_FRAMESKIP) {
            time_since_last_update -= TIME_PER_FRAME;
            update();

            loop_count++;
        }

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed && moved) {
                if (event.key.code == Keyboard::Key::Left) {
                    if (direction != "left" && direction != "right") {
                        snake.set_direction(-1, 0);
                        direction = "left";
                        moved = false;
                    }
                } else if (event.key.code == Keyboard::Key::Right) {
                    if (direction != "left" && direction != "right") {
                        snake.set_direction(1, 0);
                        direction = "right";
                        moved = false;
                    }
                } else if (event.key.code == Keyboard::Key::Up) {
                    if (direction != "up" && direction != "down") {
                        snake.set_direction(0, -1);
                        direction = "up";
                        moved = false;
                    }
                } else if (event.key.code == Keyboard::Key::Down) {
                    if (direction != "up" && direction != "down") {
                        snake.set_direction(0, 1);
                        direction = "down";
                        moved = false;
                    }
                }
            }
        }

        draw();
    }
}

void Game::update() {
    if (!snake.move()) {
        remove("highscore.txt");
        std::ofstream file("highscore.txt");
        file << highscore;
        file.close();

        std::cout << "SCORE: " << score << std::endl;
        std::cout << "HIGH SCORE: " << highscore << std::endl;
        window.close();
    }
    if (snake.get_head_bounds().intersects(fruit.getGlobalBounds())) {
        snake.add_segment();
        Vector2i coordinates = snake.find_new_fruit_coordinates();
        fruit.setPosition(coordinates.x * 35 + 17.5, coordinates.y * 35 + 67.5);
        score++;
        scoreboard.setString("SCORE: " + std::to_string(score));

        if (score >= highscore) {
            highscore = score;
            highscore_text.setString("High Score: " + std::to_string(highscore));
        }
    }
    moved = true;
}

void Game::draw() {
    window.clear();

    window.draw(fruit);
    window.draw(snake);
    window.draw(scoreboard);
    window.draw(highscore_text);
    window.draw(top_border);

    window.display();
}