#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable {
    private:
        sf::RectangleShape squares[17][17];
    public:
        Grid();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif