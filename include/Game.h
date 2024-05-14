#pragma once
#include "Snake.h"
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <string.h>

class Game {
    private:
        sf::RenderWindow window;
        sf::Clock clock;
        Snake snake;
        sf::RectangleShape fruit;
        bool moved;
        std::string direction;
        int score;
        sf::Font font;
        sf::Text scoreboard;
        sf::RectangleShape top_border;
        int highscore;
        sf::Text highscore_text;

        Grid grid;
    public:
        Game(sf::Font &font);
        void run();
        void update();
        void draw();
};