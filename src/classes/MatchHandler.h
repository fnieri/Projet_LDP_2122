/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: MatchHandler.h
* Date: 13/01/2022
*/

#ifndef __MATCHHANDLER_H
#define __MATCHHANDLER_H

#include "Animation.h"
#include "ClickableFactory.h"
#include "ScoreCalculator.h"
#include "Enums/Interaction.h"
#include "GameObjective.h"

class MatchHandler : public Animation, public GameObjective {
    bool isInteracting = false;
    Color interactionColor = Color::NONE;
    CandySpeciality interactionSpeciality = CandySpeciality::NONE;

public:
    void handleCellsToReplace(vector<vector<int>> cellsToReplace);

    vector<vector<int>> getDiagonalCells(int col, int row, int lr);

    bool handleDiagonalCells();

    void handleGravity();

    void handleStripedHorizontal(int i, int j, vector<vector<int>> cellsToMove);

    void handleStripedVertical(int i, int j, vector<vector<int>> cellsToMove);

    void handleWrapped(int i, int j, vector<vector<int>> cellsToMove, int leftDownMargin, int rightUpMargin);

    bool wrappedInRange(int i, int j, 
                        int partialVerticalOffset, int partialHorizontalOffset, 
                        int verticalLimit, int horizontalLimit);
    
    void emptyCell(int i, int j);

    void emptyCells(vector<vector<int>> cellsToEmpty) override;

    void doubleStriped(Point firstCellPosition, Point secondCellPosition, const vector<vector<int>> &cellsToMove);

    void doubleWrapped(Point firstCellPosition, Point secondCellPosition, vector<vector<int>> cellsToMove);

    void multiColorSpecial(Point firstCellPosition, Point secondCellPosition,
                           CandySpeciality speciality, Color color);

    bool doubleSpecialCandyInteraction(Point firstCellPosition, Point secondCellPosition, Color firstCellColor,
                                       Color secondCellColor, CandySpeciality firstCellSpeciality,
                                       CandySpeciality secondCellSpeciality);

    void doubleMulticolorInteraction();

    void handleWrappedStriped(Point firstCellPosition, Point secondCellPosition,
                              vector<vector<int>> cellsToMove, bool isHorizontal);


    //Functions that use score calculator
    void sendInteractionScore(Interaction);

    void sendScoreMulticolor(CandySpeciality);

    void sendIcingScore(IcingStatus);

    void sendSpecialityScore(CandySpeciality);

    void clearIcing(int i, int j);
};



#endif //TEMP_CLASSES_MATCHHANDLER_H
