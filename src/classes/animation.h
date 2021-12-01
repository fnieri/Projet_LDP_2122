#ifndef __ANIMATION_H
#define __ANIMATION_H

#include "cell.h"
#include "candyfactory.h"
#include <vector>


class Animation {
public:
    Animation();

    static void moveCellsDown(vector<vector<int>> cellsToReplace, vector<vector<Cell>> *CellVector, int margin);
};

#endif