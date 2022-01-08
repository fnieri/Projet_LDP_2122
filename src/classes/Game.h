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


class Game {
protected:
    int margin;
    vector<vector<Cell>> CellsVertex;
    int score = 0;
    int hiScore;
    bool acceptInput = true;
    bool gameOver = false;
    int movesLeft = 10;
public:
    void getInitialHighScore();

    bool contains(Point p);

    void highlight(Point p);

    void unHighlightAll();

    void setMargin(int m);

    vector<vector<Cell>> getCells();

    void setAcceptInput(bool newState);

    bool isInputAllowed();

    virtual bool checkMatches() = 0;

    virtual void moveCellsDown(vector<vector<int>>) = 0;

    virtual void moveCellsDiagonaly() = 0;

    virtual void setCellAt(CandySpeciality newSpeciality, Color newColor, int i, int j) = 0;

    void createSpecialCandy(int, int, CandySpeciality);

    bool isCandy(Cell *cell) { return cell->isCandy();; };

    bool isCandy(Cell cell) { return cell.isCandy(); };

    bool isIcing(Cell cell);

    void addToScore(int scoreToAdd);

    void saveHighscore();

    int getScore();

    void resetScore() { score = 0; };

    vector<vector<int>> findEmptyCells();

    bool remainingEmptyCells();

    int getMovesLeft();

    void setMovesLeft(int);

    void setGameState(bool);

    bool gameIsOver();

    void decreaseMovesLeft();

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

    virtual void emptyCells(vector<vector<int>> cellsToEmpty) = 0;

    void resetGame();
};


#endif //PROJET_LDP_2122_GAME_H
