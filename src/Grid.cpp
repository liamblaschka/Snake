#include "Grid.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Grid::Grid() {
    for (int row = 0; row < 17; row++) {
        for (int col = 0; col < 17; col++) {
            squares[row][col] = RectangleShape(Vector2f(35, 35));
            squares[row][col].setPosition(35 * col, 35 * row);
            if ((row + col) % 2 == 0) {
                squares[row][col].setFillColor(Color::Black);
            } else {
                squares[row][col].setFillColor(Color::Green);
            }
        }
    }
}

void Grid::draw(sf::RenderTarget& target, RenderStates states) const {
    for (int row = 0; row < 17; row++) {
        for (int col = 0; col < 17; col++) {
            target.draw(squares[row][col]);
        }
    }
}
