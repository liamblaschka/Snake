#include "Pathfinder.h"
#include "BFS.h"
#include "DFS.h"
#include "State.h"
#include "Snake.h"
#include "AI.h"
#include <string>
#include <algorithm>
#include <list>

#include <iostream>

using namespace std;

AI::AI() {}

AI::AI(string algorithm) {
    if (algorithm == "BFS") {
        pathfinder = new BFS();
        pathIndex = 0;
    } else if (algorithm == "DFS") {
        pathfinder = new DFS();
        pathIndex = 0;
    }
}

void AI::updatePath(list<State>& snakeState, State start, State goal) {
    pathIndex = 0;

    path = pathfinder->findPath(snakeState, start, goal);
    reverse(path.begin(), path.end());
}

void AI::makeMove(Snake& snake) {
    if (path.size() == 0) {
        return;
    }

    State next = path[pathIndex];
    State current = snake.getState();
    int direction_x = next.col - current.col;
    int direction_y = next.row - current.row;

    snake.set_direction(direction_x, direction_y);
    pathIndex++;
}