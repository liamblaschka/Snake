#include "Snake.h"
#include "State.h"
#include "Pathfinder.h"
#include "BFS.h"
#include "Fruit.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <iostream>

using namespace std;
using namespace sf;

Game::Game(Font &font, string player) : window(VideoMode(595, 645), "Snake", Style::Titlebar | Style::Close), ai(player), top_border(Vector2f(595, 3)) {
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    scoreboard.setFont(font);
    scoreboard.setString("SCORE: 0");
    scoreboard.setCharacterSize(35);
    scoreboard.setPosition(10, 5);
    highscore_text.setFont(font);
    highscore_text.setCharacterSize(20);
    highscore_text.setPosition(300, 3);
    top_border.setOrigin(0, 3);
    top_border.setPosition(0, 50);

    this->player = player;

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

void Game::reset() {
    scoreboard.setString("SCORE: 0");
    highscore_text.setString("HIGH SCORE: " + to_string(highscore));

    snake.reset();
    fruit.setState(State(8, 12));

    run();
}

void Game::run() {
    fruit.setState(State(8, 12));

    if (player != "human") {
        list<State> snakeState = snake.getSegmentStates();
        State start = snake.getState();
        State goal = fruit.getState();
        ai.updatePath(snakeState, start, goal);
    }


    clock.restart();
    moved = true;
    direction = "right";
    score = 0;

    alive = true;

    const int MAX_FRAMESKIP = 5;
    const Time TIME_PER_FRAME = milliseconds(125);
    Time time_since_last_update = Time::Zero;
    while (window.isOpen() && alive) {
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
                if (player == "human") {
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

        draw();
    }

    if (window.isOpen()) {
        reset();
    }
}

void Game::update() {
    if (player != "human") {
        ai.makeMove(snake);
    }

    if (!snake.move()) {
        remove("highscore.txt");
        ofstream file("highscore.txt");
        file << highscore;
        file.close();

        cout << "SCORE: " << score << endl;
        cout << "HIGH SCORE: " << highscore << endl << endl;

        alive = false;

        // window.close();
    }
    if (snake.getState().row == fruit.getState().row && snake.getState().col == fruit.getState().col) {
        snake.add_segment();
        Vector2i coordinates = snake.find_new_fruit_coordinates();

        fruit.setState(State(coordinates.y, coordinates.x));

        score++;
        scoreboard.setString("SCORE: " + to_string(score));

        if (score >= highscore) {
            highscore = score;
            highscore_text.setString("High Score: " + to_string(highscore));
        }


        if (player != "human") {
            list<State> snakeState = snake.getSegmentStates();
            State start = snake.getState();
            State goal = fruit.getState();
            ai.updatePath(snakeState, start, goal);
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
