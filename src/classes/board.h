#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "cell.h"
#include <cmath>
#include <iostream>
#include "common.h"


class Board {
    vector<Cell> CellsVertex;
    int cellSize;
    int margin;
    int numberOfCells;
public:
    Board(int cellSize, int margin, int numberOfCells);
    void draw();
    bool contains(Point p);
//    void handleClick();
};


#endif
