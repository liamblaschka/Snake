#include "State.h"
#include "Pathfinder.h"
#include <vector>
#include <unordered_map>

using namespace std;

vector<State> Pathfinder::buildPath(unordered_map<int, State>& previousState, State start, State current, int cols) {
    vector<State> path;

    while (!(current.row == start.row && current.col == start.col)) {
        path.push_back(current);
        current = previousState[current.row * cols + current.col];
    }

    return path;
}
