#pragma once
#include "Snake.h"
#include "Pathfinder.h"
#include "BFS.h"
#include "Fruit.h"
#include "AI.h"
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <string.h>

class Game {
    private:
        sf::RenderWindow window;
        sf::Clock clock;
        Snake snake;
        Fruit fruit;
        bool moved;
        std::string direction;
        int score;
        sf::Font font;
        sf::Text scoreboard;
        sf::RectangleShape top_border;
        int highscore;
        sf::Text highscore_text;
        std::string player;
        std::vector<State> path;
        AI ai;
        Grid grid;
        bool alive;
        
    public:
        Game(sf::Font &font, std::string player);
        void reset();
        void run();
        void update();
        void draw();
};