#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "cell.h"
#include <cmath>
#include <iostream>
#include "common.h"
#include <memory>
#include "candyfactory.h"
#include "matchdetection.h"

class Board {
    vector<vector<Cell>> CellsVertex;
    unique_ptr<MatchDetection> matchDetector;
    int cellSize;
    int margin;
    int numberOfCells;
    Cell *selectedCell = nullptr;
    Point selectedCellPosition;
public:
    Board(int cellSize, int margin, int numberOfCells);
    void draw();

    bool contains(Point);

    vector<vector<Cell>> getCells();
    // vector<Cell> getCells();
    //  void handleClick(Point mouseLoc);
    void checkMatches();
    void createSpecialCandy(int i, int j, CandySpeciality speciality);
    void moveCells(vector<vector<int>>);

    void swapCells(Cell *, Point);

    void exchangeCells(Cell *cell1, Cell *cell2);

    static bool isMoveAllowed(Point cell1Position, Point cell2Position);

};


#endif