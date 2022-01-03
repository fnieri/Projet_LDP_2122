#ifndef __CANVAS_H
#define __CANVAS_H

#include <vector>
#include <cmath>
#include <iostream>
#include <FL/fl_draw.H>

#include "Cell.h"
#include "Common.h"
#include "Board.h"

class Canvas: public Board {
public:
    Canvas(int cellSize, int margin, int numberOfCells);
    void draw() override;
    void keyPressed(int keyCode);
};

#endif