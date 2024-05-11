#include "Game.h"
#include "Snake.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace sf;
using namespace std;

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

    ifstream file("highscore.txt");
    if (file.is_open()) {
        string line;
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
    while (window.isOpen()) {

        update();
        draw();
    }
}

void Game::update() {
    if (clock.getElapsedTime().asMilliseconds() >= 125) {
        if (!snake.move()) {
            remove("highscore.txt");
            ofstream file("highscore.txt");
            file << highscore;
            file.close();

            cout << "SCORE: " << score << endl;
            window.close();
        }
        if (snake.get_head_bounds().intersects(fruit.getGlobalBounds())) {
            snake.add_segment();
            Vector2i coordinates = snake.find_new_fruit_coordinates();
            fruit.setPosition(coordinates.x * 35 + 17.5, coordinates.y * 35 + 67.5);
            score++;
            scoreboard.setString("SCORE: " + to_string(score));

            if (score >= highscore) {
                highscore = score;
                highscore_text.setString("High Score: " + to_string(highscore));
            }
        }
        moved = true;
        clock.restart();
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
}

void Game::draw() {
    window.clear();

    // window.draw(grid);

    window.draw(fruit);
    window.draw(snake);
    window.draw(scoreboard);
    window.draw(highscore_text);
    window.draw(top_border);
    window.display();
}