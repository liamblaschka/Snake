#pragma once
#include "Segment.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

class Snake : public sf::Drawable {
    private:
        std::vector<Segment> segments;
    public:
        Snake();
        bool move();
        void set_direction(int x, int y);
        void add_segment();
        sf::FloatRect get_head_bounds();
        sf::Vector2i find_new_fruit_coordinates();
        State getState();
        std::list<State> getSegmentStates();
        void reset();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};