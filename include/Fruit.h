#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>

class Fruit : public sf::Drawable {
    private:
        sf::RectangleShape shape;
        State state;

    public:
        Fruit() : state(0, 0) {
            shape = sf::RectangleShape(sf::Vector2f(15, 15));
            shape.setOrigin(7.5, 7.5);
        }

        void setState(State state) {
            this->state = state;
            shape.setPosition(state.col * 35 + 17.5, state.row * 35 + 67.5);
        }

        State getState() {
            return state;
        }

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(shape);
        }

};