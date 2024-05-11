#include "Snake.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <time.h>

using namespace sf;
using namespace std;

Snake::Snake() {
    srand(time(0));
    segments.push_back(Segment(Vector2i(4, 8), Vector2i(1, 0)));
}

bool Snake::move() {
    // check if move can be made
    Vector2i destination = segments[0].get_coordinates();
    Vector2i direction = segments[0].get_direction();
    destination.x += direction.x;
    destination.y += direction.y;
    if (destination.x < 0 || destination.x > 16 || destination.y < 0 || destination.y > 16) {
        return false; // can't move
    }
    for (auto itr = segments.begin(); itr != segments.end(); itr++) {
        Vector2i segment_coordinates = itr->get_coordinates();
        if (destination.x == segment_coordinates.x && destination.y == segment_coordinates.y) {
            return false; // can't move
        }
    }

    // move can be made
    for (auto itr = segments.end() - 1; itr != segments.begin(); itr--) {
        itr->move();
        itr->set_direction((itr - 1)->get_direction());
    }
    segments[0].move();
    return true;
}

void Snake::set_direction(int x, int y) {
    segments[0].set_direction(Vector2i(x, y));
}

void Snake::add_segment() {
    Vector2i direction = segments.back().get_direction();
    Vector2i coordinates = segments.back().get_coordinates();
    coordinates.x += -direction.x;
    coordinates.y += -direction.y;
    segments.push_back(Segment(coordinates, direction));
}

FloatRect Snake::get_head_bounds() {
    return segments[0].get_bounds();
}

Vector2i Snake::find_new_fruit_coordinates() {
    while(true) {
        bool valid = true;
        Vector2i coordinates(rand() % 17, rand() % 17);
        for (auto itr = segments.begin(); itr != segments.end(); itr++) {
            Vector2i segment_coordinates = itr->get_coordinates();
            if (coordinates.x == segment_coordinates.x && coordinates.y == segment_coordinates.y) {
                valid = false;
                break;
            }
        }
        if (valid) {
            return coordinates;
        }
    }
}

void Snake::draw(RenderTarget& target, RenderStates states) const {
    for (auto itr = segments.begin(); itr != segments.end(); itr++) {
        target.draw(*itr);
    }
}
