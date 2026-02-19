#pragma once
#include "Pathfinder.h"
#include "BFS.h"
#include "State.h"
#include "Snake.h"
#include <string>
#include <vector>

class AI {
    private:
        Pathfinder* pathfinder;
        std::vector<State> path;
        int pathIndex;
    public:
        AI();
        AI(std::string algorithm);
        void updatePath(std::list<State>& snakeState, State start, State goal);
        void makeMove(Snake& snake);

        ~AI() {
            delete pathfinder;
        }
};