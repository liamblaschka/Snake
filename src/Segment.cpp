#include "Segment.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Segment::Segment(Vector2i coordinates, Vector2i direction, double opacity) : segment(Vector2f(30, 30)) {
    this->coordinates = coordinates;
    this->direction = direction;
    position.x = coordinates.x * 35 + 17.5;
    position.y = coordinates.y * 35 + 67.5;

    segment.setOrigin(15, 15);
    segment.setPosition(position);
    // segment.setFillColor(Color(254, 138, 24, 255 * opacity));
    segment.setFillColor(Color(0, 255, 0, 255 * opacity));
}

void Segment::move() {
    position.x += direction.x * 35;
    position.y += direction.y * 35;
    segment.setPosition(position);

    coordinates.x += direction.x;
    coordinates.y += direction.y;
}

void Segment::set_direction(Vector2i direction) {
    this->direction = direction;
}

Vector2i Segment::get_direction() {
    return direction;
}

Vector2f Segment::get_position() {
    return position;
}

FloatRect Segment::get_bounds() {
    return segment.getGlobalBounds();
}

Vector2i Segment::get_coordinates() {
    return coordinates;
}

void Segment::set_colour(sf::Color colour) {
    segment.setFillColor(colour);
}

void Segment::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(segment);
}
