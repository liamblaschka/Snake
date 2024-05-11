#include "Game.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    Font font;
    font.loadFromFile("../../assets/ChargeVectorBold-mLyD9.ttf");
    font.setSmooth(true);
    Game game(font);
    game.run();
    return 0;
}