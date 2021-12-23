//
// Created by louis on 17/12/2021.
//

#ifndef PROJET_LDP_2122_GAME_H
#define PROJET_LDP_2122_GAME_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

#include "Candy.h"
#include "Cell.h"
#include "CandyFactory.h"
#include "CandySpeciality.h"
#include "Common.h"
#include "ClickableFactory.h"

class Game : public ClickableFactory {
protected:
    int margin;
    vector <vector<Cell>> CellsVertex;
    int score = 42069;
    bool acceptInput = true;
public:
    bool contains(Point p);

    void highlight(Point p);

    void unHighlightAll();

    void setMargin(int m);

    vector <vector<Cell>> getCells();

    void setAcceptInput(bool newState);

    bool isInputAllowed();

    virtual void moveCellsDown(vector <vector<int>>) = 0;

    virtual void setCellAt(CandySpeciality newSpeciality, Color newColor, int i, int j) = 0;

    void createSpecialCandy(int, int, CandySpeciality);

    virtual void reset() = 0;

    virtual bool handleBoardContains(Point p) = 0;

    virtual void handleBoardDrag(Point p1, Point p2) = 0;

    virtual bool isMoveAllowed(Point cell1Position, Point cell2Position) = 0;

    virtual void swapCellsNoAnim(Cell *cell1, Cell *cell2) = 0;

//    virtual bool checkMatches() = 0;

    virtual Point getPositionOfCell(Point p) = 0;

    virtual void setSelectedCell(Cell *) = 0;

    virtual Cell *cellAt(Point p) = 0;

    virtual void setSwapCell(Cell *) = 0;

    virtual void setSelectedCellPosition(Point p) = 0;

    virtual void swapCells(Cell *, Point) = 0;

    virtual void setSwapCellPosition(Point p) = 0;

    virtual void emptyCells(vector <vector<int>> cellsToEmpty) = 0;
};


#endif //PROJET_LDP_2122_GAME_H
