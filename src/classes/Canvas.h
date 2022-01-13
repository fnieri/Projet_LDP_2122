/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: Canvas.h
* Date: 13/01/2022
*/

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
    bool showSplashscreen = true;
    bool showBoard = true;
    unique_ptr<Splashscreen> splashscreen;
    int messageX = 175, messageY = 300;
public:
    Canvas(int cellSize, int margin, int numberOfCells);
    void draw() override;
    void keyPressed(int keyCode);

    
    /**
     * @brief Show splashScreen upon start
     */
    
    void showSplashScreen();

    /**
     * @brief Show current informations about:
     * Score, high score, moves left and current objective
     * 
     */
    void drawCurrentObjective();

    /**
     * @brief Check if game is over 
     *  If true, print message to screen
     */
    void checkLevelDone();
    
    void showShuffle();
    void shuffleCurrentLevel();

    void hideAll();
    void showAll();
    void showCenterMessage(std::string message);
    void showReset();

    
    
    /**
     * @brief Reset current level if game is over
     *  or upon press of r key
     */
    void resetCurrentLevel();

    //Setters
    bool isKeyInputAllowed();
    void setDrawAchievement(bool);
    void setKeyInputAllowed(bool);
    void setShowTopInfo(bool);
    void setShowBoard(bool);
    
    //Getters    
    bool getShowBoard();
    bool getShowTopInfo();
    bool getShowSplashscreen();
};


#endif