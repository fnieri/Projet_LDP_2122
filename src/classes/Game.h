/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: Game.h
* Date: 13/01/2022
*/

#ifndef __2122_GAME_H
#define __2122_GAME_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include "unistd.h"

#include "Clickable.h"
#include "Candy.h"
#include "Cell.h"
#include "CandyFactory.h"
#include "Enums/CandySpeciality.h"
#include "Common.h"
#include "ClickableFactory.h"
#include "Icing.h"
#include "Wall.h"
#include "Enums/Objective.h"


class Game{
protected:
    int margin;
    vector <vector<Cell>> CellsVertex;
    int score = 0;
    int hiScore;
    bool acceptInput = true;
    bool gameOver = false;
    bool shuffling = false;
    bool resetting = false;
    int movesLeft = 15; 
    
public:

   //Setters 
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

    void gameWait(useconds_t time);

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
    
    bool isShuffling();

    //Check if cell contains points
    bool contains(Point p);
    bool isInputAllowed();
    int getScore();
    int getMovesLeft(); 
    bool gameIsOver();
    bool isResetting();    
    bool remainingEmptyCells();

    vector<vector<int>> findEmptyCells();

    //---//

    void createSpecialCandy(int, int, CandySpeciality);
    
    virtual void moveCellsDiagonally(const vector<vector<int>> &diagonalCells, int lr) = 0;
    virtual void moveCellsDown(vector <vector<int>>) = 0;

    virtual void setCellAt(CandySpeciality newSpeciality, Color newColor, int i, int j) = 0;

    virtual void reset() = 0;

    virtual bool handleBoardContains(Point p) = 0;

    virtual void handleBoardDrag(Point p1, Point p2) = 0;

    virtual bool isMoveAllowed(Point cell1Position, Point cell2Position) = 0;

    virtual void swapCellsNoAnim(Cell *cell1, Cell *cell2) = 0;

    virtual bool checkMatches() = 0;

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
