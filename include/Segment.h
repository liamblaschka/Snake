#pragma once
#include <SFML/Graphics.hpp>

class Segment : public sf::Drawable {
    private:
        sf::RectangleShape segment;
        sf::Vector2i direction;
        sf::Vector2f position;
        sf::Vector2i coordinates;
    public:
        Segment(sf::Vector2i coordinates, sf::Vector2i direction, double opacity = 1);
        void move();
        void set_direction(sf::Vector2i direction);
        sf::Vector2i get_direction();
        sf::Vector2f get_position();
        sf::FloatRect get_bounds();
        sf::Vector2i get_coordinates();
        void set_colour(sf::Color);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};