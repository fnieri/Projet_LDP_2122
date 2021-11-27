//
// Created by frann on 27/11/21.
//

#ifndef __MATCHDETECTION_H
#define __MATCHDETECTION_H

#include <memory>
#include <vector>
#include "board.h"
#include "candyspeciality.h"
#include <cmath>
#include <iostream>
#include "common.h"
#include <memory>
#include "candyfactory.h"

class MatchDetection {
    private:
        Board *candyBoard;
        vector<vector<Cell>> CellsVertex;
        static const int matchFive[2][2][4];
        static const int wrappedCandy[6][2][2];
        static const int matchHorizontalFour[2][3];
        static const int matchVerticalFour[2][3];
        static const int matchHorizontal[2][3];
        static const int matchVertical[2][3];
    public:
        MatchDetection(Board *board);

        void checkMatches();

        bool checkMatchFive(int i, int j);

        bool checkWrappedCandy(int i, int j);

        bool checkHorizontalMatchFour(int i, int j);

        bool checkVerticalMatchFour(int i, int j);
        
        bool checkHorizontalMatch(int i, int j);

        bool checkVerticalMatch(int i, int j);


        bool checkForCandiesInteraction(Candy firstCandy, Candy secondCandy);

        bool doubleBombInteraction();


};

#endif //__MATCHDETECTION_H
