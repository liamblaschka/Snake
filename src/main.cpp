#include "Game.h"
#include <string>
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace std;
using namespace sf;

int main(int argc, char* argv[]) {
    Font font;
    font.loadFromFile("../../assets/ChargeVectorBold-mLyD9.ttf");
    font.setSmooth(true);

    string player;
    if (argc == 1) {
        player = "human";
    } else {
        player = string(argv[1]);
    }

    Game game(font, player);

    game.run();
    return 0;
}