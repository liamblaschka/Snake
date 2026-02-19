#pragma once
#include "State.h"
#include <vector>
#include <unordered_map>
#include <list>

class Pathfinder {
    protected:
        int direction[4][2] = {
            {0, 1},     // Right
            {1, 0},     // Down
            {0, -1},    // Left
            {-1, 0}     // Up
        };

        std::vector<State> buildPath(std::unordered_map<int, State>& previousState, State start, State current, int cols);
    public:
        virtual std::vector<State> findPath(std::list<State>& snakeState, State start, State end) = 0;

        virtual ~Pathfinder() {}
};