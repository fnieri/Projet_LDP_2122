#ifndef __CANVAS_H
#define __CANVAS_H

#include <vector>
#include <cmath>
#include <iostream>
#include <FL/fl_draw.H>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "Cell.h"
#include "Common.h"
#include "Board.h"
#include "Splashscreen.h"

class Canvas: public Board, public Splashscreen {
    bool showSplashscreen;
public:
    Canvas(int cellSize, int margin, int numberOfCells, const char *filename);
    void draw() override;
    void keyPressed(int keyCode);
};

#endif