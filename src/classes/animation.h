#ifndef __ANIMATION_H
#define __ANIMATION_H

#include "cell.h"
#include "candyfactory.h"
#include "board.h"
#include <vector>

class Board;

class Animation {

public:
    Animation();
    static void emptyCell(vector<vector<Cell>> *CellVector, int i, int j);

    static void emptyCells(vector<vector<int>> cellsToEmpty, vector<vector<Cell>> *CellVector);
    
    static void handleWrapped(Board *board, vector<vector<Cell>> *CellVector, int i, int j, int leftDownMargin, int rightUpMargin);
    
    static void handleStrippedHorizontal(Board *board, vector<vector<Cell>> *CellVector, int i, int j);

    static void handleStrippedVertical(Board *board, vector<vector<Cell>> *CellVector, int i, int j);

    static void
    moveCellsDown(Board *board, vector<vector<int>> cellsToReplace, vector<vector<Cell>> *CellVector, int margin);

};

#endif