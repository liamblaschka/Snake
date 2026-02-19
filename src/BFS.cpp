#include "State.h"
#include "Pathfinder.h"
#include "BFS.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <list>

using namespace std;

vector<State> BFS::findPath(list<State>& snakeState, State start, State goal) {
    int rows = 17;
    int cols = 17;

    queue<State> stateQueue;
    queue<list<State>> snakeQueue;
    stateQueue.push(start);
    snakeQueue.push(snakeState);
    unordered_map<int, State> previousState;

    previousState[start.row * cols + start.col] = start;

    while (!stateQueue.empty()) {
        State currentState = stateQueue.front();
        stateQueue.pop();

        list<State> currentSnake = snakeQueue.front();

        snakeQueue.pop();

        vector<vector<char>> gameState(rows, vector<char>(cols, '1'));
        int i = 0;
        for (auto itr = currentSnake.begin(); itr != currentSnake.end(); ++itr) {
            if (itr != prev(currentSnake.end()) || i == 1) {
                if (itr->row >= 0 && itr->row < rows && itr->col >= 0 && itr->col < cols) {
                    gameState[itr->row][itr->col] = 'X';
                }
            }
            i++;
        }
        currentSnake.pop_back();

        if (currentState.row == goal.row && currentState.col == goal.col) {
            return buildPath(previousState, start, currentState, cols);
        }

        for (int i = 0; i < 4; i++) {
            int row = currentState.row + direction[i][0];
            int col = currentState.col + direction[i][1];
            if ((row >= 0 && row < rows && col >= 0 && col < cols) && gameState[row][col] != 'X') {
                if (previousState.find(row * cols + col) == previousState.end()) {
                    stateQueue.push(State(row, col));
                    previousState[row * cols + col] = currentState;

                    list<State> newSnakeState = currentSnake;
                    newSnakeState.push_front(State(row, col));
                    snakeQueue.push(newSnakeState);
                }
            }
        }
    }

    return {};
}
