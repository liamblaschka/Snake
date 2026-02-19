#pragma once
#include "State.h"
#include "Pathfinder.h"
#include <vector>
#include <unordered_map>
#include <list>

class DFS : public Pathfinder {
    private:
        std::vector<State> helper(std::list<State> snakeState, State start, State current, State goal, std::unordered_map<int, State>& previousState);

    public:
        std::vector<State> findPath(std::list<State>& snakeState, State start, State end) override;

        ~DFS() {}
};