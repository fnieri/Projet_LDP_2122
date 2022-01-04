#include "Canvas.h"

Canvas::Canvas(int cellSize, int margin, int numberOfCells, const char* filename) : 
Board(cellSize, margin, numberOfCells), splashscreen{filename} {
    objectiveInit();
}

void Canvas::draw() {
    showSplashScreen();
    showReset();
    
    drawCurrentObjective();
    // at the moment only the nearest sqrt of numberOfCells is displayed. If 20 cells, then 16 cells are shown.
    if (drawBoard())
        Board::draw();

    
}

void Canvas::showSplashScreen() {
    if (showSplashscreen) {
        splashscreen.draw(0, 0, splashscreen.w(), splashscreen.h());
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
        
        checkLevelDone();
        
        string scoreStr = "Score: " + to_string(score);
        string hiScoreStr = "High score: " + to_string(hiScore);
        string achievementStr = getObjectiveString(); 
        string movesStr = "Moves left:" + to_string(getMovesLeft());

        fl_draw(scoreStr.c_str(), 60, 20);
        fl_draw(hiScoreStr.c_str(), 150, 20);
        fl_draw(movesStr.c_str(), 550, 20);
        
        if (drawAchievement)
            fl_draw(achievementStr.c_str(), 280, 20);
    }
    else {
        checkLevelDone();
    }
}

void Canvas::checkLevelDone() {

    if (objectiveIsComplete()) {
        setDrawAchievement(false); setAcceptInput(false);
        setShowBoard(false); setShowTopInfo(false);
        
        fl_rectf(messageX, messageY, 300, 40, FL_WHITE);
        fl_rect(messageX, messageY, 300, 40, FL_BLACK);
    
        fl_draw("You completed the level !", messageX + 10, messageY + 20);
    }
    else if (gameIsOver() && !objectiveIsComplete()) {
        setDrawAchievement(false);  setAcceptInput(false);
        setShowBoard(false); setShowTopInfo(false);
        
        fl_rectf(messageX, messageY, 300, 40, FL_WHITE);
        fl_rect(messageX, messageY, 300, 40, FL_BLACK);
        fl_draw("You lost! Press r to restart level!", messageX + 10, messageY + 20);
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
        case 'c':
            checkMatches();
            break;
        case 's':
            shuffle();
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
    //Hide resetting process
    
    setShowBoard(false);
    setDrawAchievement(false);
    setShowTopInfo(false);
    setResetting(true);

    reset();
    resetScore();
    setMovesLeft(30);
    objectiveInit();
    matchIcingObjective();
    
    setResetting(false);
    setDrawAchievement(true);
    setShowBoard(true);
    setShowTopInfo(true);
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

bool Canvas::drawBoard() {
    return showBoard;
}

void Canvas::showReset() { 
    if (isResetting()) {
        fl_rectf(messageX, messageY, 300, 40, FL_WHITE);
        fl_rect(messageX, messageY, 300, 40, FL_BLACK);
        
        fl_draw("Resetting the level, hold on", messageX + 10, messageY + 20);
    }
}

void Canvas::setResetting(bool newState) {
    resetting = newState;
}

bool Canvas::isResetting() {
    return resetting;
}