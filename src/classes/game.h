//
// Created by louis on 17/12/2021.
//

#ifndef PROJET_LDP_2122_GAME_H
#define PROJET_LDP_2122_GAME_H

#include <vector>
#include "cell.h"


class Game {
protected:
    vector<vector<Cell>> CellsVertex;
    int score = 42069;
public:
    Game();
    virtual void moveCells(vector<vector<int>>) {};

    virtual void setCellAt(CandySpeciality newSpeciality, Color newColor, int i, int j) {};

    virtual void createSpecialCandy(int, int, CandySpeciality) {};

    virtual vector<vector<Cell>> getCells() {};

    virtual void reset() {};

    virtual bool isMoveAllowed(Point cell1Position, Point cell2Position);

    virtual void swapCellsNoAnim(Cell *cell1, Cell *cell2);

    virtual bool checkMatches() {};

    virtual Point getPositionOfCell(Point p) {};

    virtual void setSelectedCell(Cell *) {};

    virtual Cell *cellAt(Point p) {};

    virtual void setSwapCell(Cell *) {};

    virtual void setAcceptInput(bool newState) {};

    virtual void swapCells(Cell *, Point) {};
};


#endif //PROJET_LDP_2122_GAME_H
