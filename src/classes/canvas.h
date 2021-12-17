#ifndef __CANVAS_H
#define __CANVAS_H

#include <vector>
#include "common.h"
#include "cell.h"
#include "board.h"
#include "board.h"
#include <cmath>
#include <iostream>
#include <FL/fl_draw.H>

class Canvas: public Board {
public:
    Canvas(int cellSize, int margin, int numberOfCells);
    void draw() override;
    void keyPressed(int keyCode);
};

#endif