#ifndef __ANIMATION_H
#define __ANIMATION_H

#include "cell.h"
#include "candyfactory.h"
#include "board.h"
#include <vector>

class Board;

class Animation {
    static void handleStrippedHorizontal(Board *board, vector<vector<Cell>> *CellVector, int i, int j);

    static void handleStrippedVertical(Board *board, vector<vector<Cell>> *CellVector, int i, int j);

    static void handleWrapped(Board *board, vector<vector<Cell>> *CellVector, int i, int j);

    static void emptyCell(vector<vector<Cell>> *CellVector, int i, int j);

    static void emptyCells(vector<vector<int>> cellsToEmpty, vector<vector<Cell>> *CellVector);

public:
    Animation();

    static void
    moveCellsDown(Board *board, vector<vector<int>> cellsToReplace, vector<vector<Cell>> *CellVector, int margin);
};

#endif