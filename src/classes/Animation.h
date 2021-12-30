//
// Created by louis on 19/12/2021.
//

#ifndef TEMP_CLASSES_ANIMATION_H
#define TEMP_CLASSES_ANIMATION_H

#include "Game.h"


class Animation : virtual public Game {
public:
    void moveCellsDown(vector <vector<int>> cellsToReplace) override;
    void destroyCandy(Cell *cell);
};

#endif //TEMP_CLASSES_ANIMATION_H
