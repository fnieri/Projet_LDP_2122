//
// Created by louis on 17/12/2021.
//

#ifndef PROJET_LDP_2122_GAME_H
#define PROJET_LDP_2122_GAME_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include "unistd.h"

#include "../Clickables/Clickable.h"
#include "../Clickables/Candy.h"
#include "../Display/Cell.h"
#include "../Factories/CandyFactory.h"
#include "../Enums/CandySpeciality.h"
#include "../Sources/Common.h"
#include "../Factories/ClickableFactory.h"
#include "../Clickables/Icing.h"
#include "../Clickables/Wall.h"
#include "../Enums/Objective.h"


class Game{
protected:
    int margin;
    vector <vector<Cell>> CellsVertex;
    int score = 0;
    int hiScore;
    bool acceptInput = true;
    bool gameOver = false;
    bool animating = false;
    bool shuffling = false;
    bool resetting = false;
    int movesLeft = 1; 
    
public:

   //Setters 
    void setAnimating(bool);
    void setMargin(int m);
    void setShuffling(bool);
    void setAcceptInput(bool newState);
    void resetScore() {score = 0;};
    void setMovesLeft(int);
    void setGameState(bool);
    void decreaseMovesLeft();
    void addToScore(int scoreToAdd);
    void setResetting(bool);
    //----//

    //Save highscore in file
    void saveHighscore();

    //Cell highlighting
    void highlight(Point p);
    void unHighlightAll();

    
    //Getters
    void getInitialHighScore();  
    
    //Check if cell is of clickable derived class
    bool isCandy(Cell *cell);
    bool isCandy(Cell cell);
    bool isIcing(Cell cell);
    
    //Get board cells
    vector <vector<Cell>> getCells();
    
    //Reset moves and state
    void resetGame();
    
    //Check if animation is animating
    bool isAnimating();
    bool isShuffling();

    //Check if cell contains points
    bool contains(Point p);
    bool isInputAllowed();
    int getScore();
    int getMovesLeft(); 
    bool gameIsOver();
    bool isResetting();
    //---//

    void createSpecialCandy(int, int, CandySpeciality);
    
    virtual void moveCellsDown(vector <vector<int>>) = 0;

    virtual void setCellAt(CandySpeciality newSpeciality, Color newColor, int i, int j) = 0;

    virtual void reset() = 0;

    virtual bool handleBoardContains(Point p) = 0;

    virtual void handleBoardDrag(Point p1, Point p2) = 0;

    virtual bool isMoveAllowed(Point cell1Position, Point cell2Position) = 0;

    virtual void swapCellsNoAnim(Cell *cell1, Cell *cell2) = 0;

//    virtual bool checkMatches() = 0;

    virtual Point getPositionOfCell(Point p) = 0;

    virtual void setSelectedCell(Cell *) = 0;

    virtual Cell *cellAt(Point p) = 0;

    virtual void setSwapCell(Cell *) = 0;

    virtual void setSelectedCellPosition(Point p) = 0;

    virtual void swapCells(Cell *, Point) = 0;

    virtual void setSwapCellPosition(Point p) = 0;

    virtual void emptyCells(vector <vector<int>> cellsToEmpty) = 0;


};



#endif //PROJET_LDP_2122_GAME_H