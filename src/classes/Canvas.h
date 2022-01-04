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
    bool showTopInfo = true;
    bool showSplashscreen = false;
    bool showBoard = true;
    bool resetting = false;

    int messageX= 175, messageY = 300;
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

    void setShowTopInfo(bool);

    bool getShowTopInfo();

    bool drawBoard();

    void setShowBoard(bool);

    void showReset();

    void setResetting(bool);

    bool isResetting();
};


#endif