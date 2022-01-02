//
// Created by louis on 19/12/2021.
//

#ifndef __ANIMATION_H
#define __ANIMATION_H

#include "Game.h"


class Animation : virtual public Game {
public:
    void moveCellsDown(vector <vector<int>> cellsToReplace) override;
    
    void destroyObject(Cell *cell);
};

#endif
