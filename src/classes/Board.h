//
// Created by louis on 19/12/2021.
//

#ifndef __BOARD_H
#define __BOARD_H

#include <thread>

#include "EventHandler.h"
#include "MatchDetection.h"
#include "LevelFactory.h"
#include "Enums/Interaction.h"

class Board : public EventHandler, public MatchDetection {
    int cellSize;
    int numberOfCells;
    Cell *selectedCell = nullptr;
    Point selectedCellCenter{0, 0};
    Point selectedCellPosition{0, 0};
    Cell *toSwapCell = nullptr;
    Point toSwapCellCenter{0, 0};
    Point toSwapCellPosition{0, 0};
    vector<Cell *> suggestedCells{};
    bool runSuggestionThread = false;
public:
    Board(int cellSize, int margin, int numberOfCells);

    void reset() override;

    Cell *cellAt(Point p) override;

    Point getPositionOfCell(Point p) override;

    void setSelectedCell(Cell *newCell) override;

    void setSelectedCellPosition(Point p) override;

    void setSwapCell(Cell *newCell) override;

    void setSwapCellPosition(Point p) override;

    void setCellAt(CandySpeciality speciality, Color newColor, int i, int j) override;

    void swapCells(Cell *swapCell, Point swapCellPosition) override;

    void swapCellsNoAnim(Cell *cell1, Cell *cell2) override;

    bool isMoveAllowed(Point cell1Position, Point cell2Position) override;

    bool handleBoardContains(Point p) override;

    void handleBoardDrag(Point p1, Point p2) override;

    bool checkIfShuffleIsNeeded();

    Cell *getCellFromPosition(Point p);

    virtual void draw();

    void shuffle();

    void exchangeCells(Cell *cell1, Cell *cell2);

    void initializeLevel();

    void terminateSuggestionsThreads();

    void handleSuggestionThread();

};


#endif //TEMP_CLASSES_BOARD_H
