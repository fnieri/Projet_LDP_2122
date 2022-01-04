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

class Canvas: public Board {
    bool drawAchievement = true;
    bool keyInputAllowed = true;
    bool showSplashscreen = true;
    Splashscreen splashscreen;
public:
    Canvas(int cellSize, int margin, int numberOfCells, const char* filename);
    void draw() override;
    void keyPressed(int keyCode);

    void showSplashScreen();

    void drawCurrentObjective();

    void checkLevelDone();
    
    void setDrawAchievement(bool);
    
    bool isKeyInputAllowed();
    
    void setKeyInputAllowed(bool);
    
    void resetCurrentLevel();
    
};

#endif