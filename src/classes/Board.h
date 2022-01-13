/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: Board.h 
* Date: 13/01/2022
*/

#ifndef __BOARD_H
#define __BOARD_H


#include <thread>
#include <mutex>

#include "EventHandler.h"
#include "MatchDetection.h"
#include "LevelFactory.h"
#include "GameObjective.h"
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

    /**
     * @brief Generate new candies upon pressing r
     */
    void reset() override;

    //Getters
    
    //Get cell from fltk point
    Cell *cellAt(Point p) override;
    //Get cell from i,j point
    Cell *getCellFromPosition(Point p);
    //Get i,j of point
    Point getPositionOfCell(Point p) override;

    //Setters
    void setSelectedCell(Cell *newCell) override;
    void setSelectedCellPosition(Point p) override;
    void setSwapCell(Cell *newCell) override;
    void setSwapCellPosition(Point p) override;
    
    /*
    * @brief Change CellsVector content from one clickable
    * to another 
    */
    void setCellAt(CandySpeciality speciality, Color newColor, int i, int j) override;
    /*
    * @brief Swap cells in vector based on position
    */
    void swapCells(Cell *swapCell, Point swapCellPosition) override;

    /*
    * @brief Swap cells without animation 
    */
    void swapCellsNoAnim(Cell *cell1, Cell *cell2) override;

    bool checkIfShuffleIsNeeded();

    bool isMoveAllowed(Point cell1Position, Point cell2Position) override;

    //Mouse events handlers
    bool handleBoardContains(Point p) override;
    void handleBoardDrag(Point p1, Point p2) override;

    virtual void draw();

    void shuffle();
    /**
     * @brief Exchange two cells when swapping
     * 
     * @param cell1 
     * @param cell2 
     */
    void exchangeCells(Cell *cell1, Cell *cell2);

    /**
     * @brief Create icing cells when objective 
     * is of type CLEAR_ICING,
     */
    void matchIcingObjective();

    void initializeLevel();

    void handleSuggestionThread();

    void resetHighlighting();

};


#endif //TEMP_CLASSES_BOARD_H
