#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "cell.h"
#include <cmath>
#include <iostream>
#include "common.h"
#include <memory>
#include "candyfactory.h"

class Board {
    vector<vector<Cell>> CellsVertex;
    int cellSize;
    int margin;
    int numberOfCells;
    Cell *selectedCell = nullptr;
public:
    Board(int cellSize, int margin, int numberOfCells);

    void draw();

    bool contains(Point);

    // vector<Cell> getCells();
    //  void handleClick(Point mouseLoc);
    void checkMatches();

    bool checkHorizontalMatch(int, int);

    bool checkVerticalMatch(int, int);

    bool checkHorizontalMatchFour(int, int);

    bool checkMatchFive(int, int);

    bool checkVerticalMatchFour(int, int);

    void moveCells(vector<vector<int>>);

    void createSpecialCandy(int, int, CandySpeciality);

    bool checkWrappedCandy(int, int);

    void swapCells(Cell*);
};


#endif