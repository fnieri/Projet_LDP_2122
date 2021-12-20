#ifndef __ANIMATION_H
#define __ANIMATION_H

#include "cell.h"
#include "candyfactory.h"
#include "board.h"
#include <vector>
#include<algorithm>

class Animation : public Game {
public:
    Animation();

    static void
    moveCellsDown(vector<vector<int>> cellsToReplace, vector<vector<Cell>> *CellVector, int margin);
};

#endif