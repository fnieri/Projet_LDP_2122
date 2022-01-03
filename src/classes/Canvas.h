#ifndef __CANVAS_H
#define __CANVAS_H

#include <vector>
#include <cmath>
#include <iostream>
#include <FL/fl_draw.H>

#include "Cell.h"
#include "Common.h"
#include "Board.h"
#include "Splashscreen.h"

class Canvas: public Board, public Splashscreen {
    // change this to true if you want to see the splashscreen and vice versa
    bool showSplashscreen = true;
public:
    Canvas(int cellSize, int margin, int numberOfCells, const char *filename);
    void draw() override;
    void keyPressed(int keyCode);
};

#endif