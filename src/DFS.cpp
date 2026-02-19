#include "State.h"
#include "Pathfinder.h"
#include "DFS.h"
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

vector<State> DFS::helper(list<State> snakeState, State start, State current, State goal, unordered_map<int, State>& previousState) {
    int rows = 17;
    int cols = 17;

    if (current.row == goal.row && current.col == goal.col) {
        return buildPath(previousState, start, goal, cols);
    }

    vector<vector<char>> gameState(rows, vector<char>(cols, '1'));
    for (auto itr = snakeState.begin(); itr != snakeState.end(); ++itr) {
        if (itr->row >= 0 && itr->row < rows && itr->col >= 0 && itr->col < cols) {
            gameState[itr->row][itr->col] = 'X';
        }
    }

    for (int i = 0; i < 4; i++) {
        int row = current.row + direction[i][0];
        int col = current.col + direction[i][1];

        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            if (gameState[row][col] != 'X') {

                
                if (previousState.find(row * cols + col) == previousState.end()) {
                    list<State> currentSnake = snakeState;
                    currentSnake.pop_back();
                    currentSnake.push_front(State(row, col));
                    previousState[row * cols + col] = current;
                    vector<State> foundPath = helper(currentSnake, start, State(row, col), goal, previousState);

                    if (!foundPath.empty()) {
                        return foundPath;
                    }
                }
            }
        }
    }

    return {};
}

vector<State> DFS::findPath(list<State>& snakeState, State start, State goal) {
    unordered_map<int, State> previousState;
    previousState[start.row * 17 + start.col] = start;

    return helper(snakeState, start, start, goal, previousState);
}
