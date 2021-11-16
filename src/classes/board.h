#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "cell.h"
#include <cmath>
#include <iostream>

class Board {
    vector<Cell> CellsVertex;
    int cellSize;
    int margin;
    int numberOfCells;
public:
    Board(int cellSize, int margin, int numberOfCells);
    void draw();
    void handleClick();
};


#endif
