#pragma once
#include "State.h"
#include "Pathfinder.h"
#include <vector>
#include <list>

class BFS : public Pathfinder {
    public:
        std::vector<State> findPath(std::list<State>& snakeState, State start, State end) override;

        ~BFS() {}
};