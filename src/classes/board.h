#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "cell.h"
#include <cmath>
#include <iostream>
#include "common.h"
#include <memory>
#include "candyfactory.h"
#include "color.h"
#include "animation.h"

class Board {
    vector<vector<Cell>> CellsVertex;
    int cellSize;
    int margin;
    int numberOfCells;
    Cell *selectedCell = nullptr;
    Point selectedCellCenter{0,0};
    Point selectedCellPosition{0,0};
public:
    Board(int cellSize, int margin, int numberOfCells);

    void reset();

    void draw();

    bool contains(Point);

    bool checkMatches();

    bool checkHorizontalMatch(int, int);

    bool checkVerticalMatch(int, int);

    bool checkHorizontalMatchFour(int, int);

    bool checkMatchFive(int, int);

    bool checkVerticalMatchFour(int, int);

    void moveCells(vector<vector<int>>);

    void createSpecialCandy(int, int, CandySpeciality);

    bool checkWrappedCandy(int, int);

    void swapCells(Cell *, Point);

    static void exchangeCells(Cell *cell1, Cell *cell2);

    static bool isMoveAllowed(Point cell1Position, Point cell2Position);

    void handleDrag(Point p);

    void handleRelease();

    void handleMove(Point p);
};


#endif