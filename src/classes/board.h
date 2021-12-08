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
#include "matchdetection.h"

class MatchDetection;

class Board {
    unique_ptr<MatchDetection> matchDetector;
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

    vector<vector<Cell>> getCells();

    bool checkMatches();

    void moveCells(vector<vector<int>>);

    void createSpecialCandy(int, int, CandySpeciality);

    void swapCells(Cell *, Point);

    static void exchangeCells(Cell *cell1, Cell *cell2);

    static bool isMoveAllowed(Point cell1Position, Point cell2Position);

    void highlight(Point p);

    void shuffle();

    static void swapCellsNoAnim(Cell *cell1, Cell *cell2);
};


#endif