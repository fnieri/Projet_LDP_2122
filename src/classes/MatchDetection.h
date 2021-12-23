#ifndef __MATCHDETECTION_H
#define __MATCHDETECTION_H

#include <memory>
#include <vector>
#include <cmath>
#include <iostream>
#include <memory>

#include "MatchHandler.h"


class MatchDetection : public MatchHandler {
    Color currentCellColor;
    Bool handleMatch;
public:

    Color getCellColor(int x, int y);

    bool cellsColorMatch(int i, int j);

    void setHandleMatch(bool handleM);

    bool checkMatches();

    bool checkMatch(vector <array<int, 2>> match, int i, int j, CandySpeciality speciality);

    bool checkMatchFive(int i, int j);

    bool checkWrappedCandy(int i, int j);

    bool checkHorizontalMatchFour(int i, int j);

    bool checkVerticalMatchFour(int i, int j);

    bool checkMatchThree(int i, int j);

    bool
    checkForCandiesInteraction(Cell *firstCell, Point firstCellPosition, Cell *secondCell, Point secondCellPosition);

    bool canStillPlay();
};

#endif //__MATCHDETECTION_H
