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
#include "eventhandler.h"

class MatchDetection;
class EventHandler;

class Board {
    vector<vector<Cell>> CellsVertex;
    unique_ptr<MatchDetection> matchDetector;
    unique_ptr<EventHandler> eventHandler;
    int cellSize;
    int margin;
    int numberOfCells;
    Cell *selectedCell = nullptr;
    Point selectedCellCenter{0,0};
    Point selectedCellPosition{0,0};
    Cell *toSwapCell = nullptr;
    Point toSwapCellCenter{0,0};
    Point toSwapCellPosition{0,0};
    bool acceptInput;
public:
    Board(int cellSize, int margin, int numberOfCells);
    void reset();

    void draw();

    Point getCellCenter(Cell*);

    Point getCellCenterFromPoint(Point p);

    Cell* cellAt(Point p);

    bool contains(Point);

    vector<vector<Cell>> getCells();

    void checkMatches();

    void handleDrag(Point p);

    void setSelectedCell(Cell*);

    void setSelectedCellPosition(Point p);

    void setSwapCell(Cell*);
    
    void setSwapCellPosition(Point p);

    Point getPositionOfCell(Point p);

    void moveCells(vector<vector<int>>);

    void createSpecialCandy(int, int, CandySpeciality);

    void setMargin(int newMargin);
    
//    bool checkWrappedCandy(int, int);

    void swapCells(Cell *, Point);

    void setAcceptInput(bool newState);

    bool getAcceptInput();
    
    void exchangeCells(Cell *cell1, Cell *cell2);

    static bool isMoveAllowed(Point cell1Position, Point cell2Position);
};


#endif

