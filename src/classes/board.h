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
    Point selectedCellCenter{0, 0};
    Point selectedCellPosition{0, 0};
    Cell *toSwapCell = nullptr;
    Point toSwapCellCenter{0, 0};
    Point toSwapCellPosition{0, 0};
    bool acceptInput = true;
protected:
    int score = 42069;
public:
    Board(int cellSize, int margin, int numberOfCells);

    void reset();

    virtual void draw();

    bool contains(Point);

    void handleMouseEvent(Point p);

    //Getters
    bool isInputAllowed();

    Cell *cellAt(Point p);

    vector<vector<Cell>> getCells();

    Point getPositionOfCell(Point p);

    void moveCells(vector<vector<int>>);
    //Setters

    void setSelectedCell(Cell *);

    void setSelectedCellPosition(Point p);

    void swapCells(Cell *, Point);

    void setSwapCell(Cell *);

    void setSwapCellPosition(Point p);

    void setAcceptInput(bool newState);

    void setCellAt(CandySpeciality newSpeciality, Color newColor, int i, int j);

    //Candies interaction
    bool checkMatches();

    void createSpecialCandy(int, int, CandySpeciality);

    void exchangeCells(Cell *cell1, Cell *cell2);

    static bool isMoveAllowed(Point cell1Position, Point cell2Position);

    void highlight(Point p);

    void shuffle();

    static void swapCellsNoAnim(Cell *cell1, Cell *cell2);

    void checkIfShuffleIsNeeded();

    void unHighlightAll();
};


#endif

