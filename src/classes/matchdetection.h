#ifndef __MATCHDETECTION_H
#define __MATCHDETECTION_H

#include <memory>
#include <vector>
#include "candyspeciality.h"
#include <cmath>
#include <iostream>
#include "common.h"
#include <memory>
#include "candyfactory.h"
#include "candyfactory.h"
#include "game.h"


class MatchDetection : virtual public Game, public MatchHandler {
    Color currentCellColor;

public:
    MatchDetection();

    Color getCellColor(int x, int y);

    bool cellsColorMatch(int i, int j);

    bool checkMatches();

    bool checkMatch(vector<array<int, 2>> match, int i, int j, CandySpeciality speciality);

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
