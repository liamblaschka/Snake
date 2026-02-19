#pragma once

struct State {
    int row;
    int col;

    State() {}
    State(int row, int col): row(row), col(col) {}
};