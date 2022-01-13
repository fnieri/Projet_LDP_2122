/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: Canvas.cpp
* Date: 13/01/2022
*/
        

#include "Canvas.h"

Canvas::Canvas(int cellSize, int margin, int numberOfCells) : 
Board(cellSize, margin, numberOfCells) {
    if (getShowSplashscreen()) {
        const char* filename = "sprites/splashscreen/splashscreen.png";
        splashscreen = make_unique<Splashscreen>(filename);
    }
    objectiveInit();
}

void Canvas::draw() {
    showSplashScreen();
    showReset();
    showShuffle();
    drawCurrentObjective();
    
    if (getShowBoard()) {
        Board::draw();
    }
}

void Canvas::showSplashScreen() {
    if (getShowSplashscreen()) {
        splashscreen->draw(0, 0, splashscreen->w(), splashscreen->h());
        Fl::check();
        sleep(2);
        showSplashscreen = false;
        Fl::check();
    }
    
}

void Canvas::drawCurrentObjective() {
    if (getShowTopInfo()) {
        fl_color(FL_WHITE);
        fl_rectf(50, 45, 605, 605, FL_WHITE);
        fl_rectf(50, 0, 605, 40, FL_WHITE);
        fl_rect(50, 0, 605, 40, FL_BLACK);
        fl_rect(50, 45, 605, 605, FL_BLACK);
        
        
        string scoreStr = "Score: " + to_string(score);
        string hiScoreStr = "High score: " + to_string(hiScore);
        string objectiveStr = getObjectiveString(); 
        string movesStr = "Moves left:" + to_string(getMovesLeft());

        fl_draw(scoreStr.c_str(), 60, 20);
        fl_draw(hiScoreStr.c_str(), 150, 20);
        fl_draw(movesStr.c_str(), 550, 20);
        
        if (drawAchievement)
            fl_draw(objectiveStr.c_str(), 280, 20);
    }
    checkLevelDone();
}

void Canvas::checkLevelDone() {
    std::string message;
    bool levelDone = false;
       if (objectiveIsComplete()) {
            levelDone = true;
            message = "You completed the level ! Press r to reset" ;
        }
        else if (gameIsOver() && !objectiveIsComplete()) {
            levelDone = true;
            message = "You lost! Press r to reset";
        }

        if (levelDone) {
            hideAll();
            showCenterMessage(message);
        }  
}


void Canvas::keyPressed(int keyCode) {
    setKeyInputAllowed(false); setAcceptInput(false);
    switch (keyCode) {
        case 'q':
            exit(0);
        case 'r':
            resetCurrentLevel();
            break;
        default:
            break;
    }
    
    setKeyInputAllowed(true); setAcceptInput(true);
}

void Canvas::setDrawAchievement(bool newDraw) {
    drawAchievement = newDraw;
}

bool Canvas::isKeyInputAllowed() {return keyInputAllowed;}

void Canvas::setKeyInputAllowed(bool newState) {
    keyInputAllowed = newState;
}

void Canvas::resetCurrentLevel() {
    hideAll();
    setResetting(true);

    setMovesLeft(30);
    reset();
    objectiveInit();
    matchIcingObjective();
    resetScore();
    
    setResetting(false);
    showAll();
}

void Canvas::setShowTopInfo(bool newShow) {
    showTopInfo = newShow;
}

bool Canvas::getShowTopInfo() {
    return showTopInfo;
}

void Canvas::setShowBoard(bool newHide) {
    showBoard = newHide;
}

bool Canvas::getShowBoard() {
    return showBoard;
}

void Canvas::showReset() { 
    if (isResetting()) {
        showCenterMessage("Resetting the level, hold on");
    }
}


void Canvas::shuffleCurrentLevel() {
    hideAll();
    setShuffling(true);

    shuffle();
    
    setShuffling(false);
    showAll();
    
}
void Canvas::showShuffle() {
    if (isShuffling()) {
        hideAll();
        showCenterMessage("Shuffling");
        showAll();
    }
}

void Canvas::hideAll() {
    setKeyInputAllowed(false);
    setAcceptInput(false);
    setShowBoard(false);
    setDrawAchievement(false);
    setShowTopInfo(false);
    
}

void Canvas::showAll() {
    setKeyInputAllowed(true);
    setDrawAchievement(true);
    setShowBoard(true);
    setShowTopInfo(true);
    setAcceptInput(true);
}

void Canvas::showCenterMessage(std::string message) {
    fl_rectf(messageX, messageY, 300, 40, FL_WHITE);
    fl_rect(messageX, messageY, 300, 40, FL_BLACK);
    fl_draw(message.c_str(), messageX + 40, messageY + 20);
}

bool Canvas::getShowSplashscreen() {
    return showSplashscreen;
}