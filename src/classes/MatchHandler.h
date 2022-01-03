//
// Created by louis on 19/12/2021.
//

#ifndef TEMP_CLASSES_MATCHHANDLER_H
#define TEMP_CLASSES_MATCHHANDLER_H

#include "Animation.h"

class MatchHandler : public Animation {
    bool isInteracting = false;
    Color interactionColor = Color::NONE;
    CandySpeciality interactionSpeciality = CandySpeciality::NONE;
public:
    void handleCellsToReplace(vector<vector<int>> cellsToReplace);

    void handleStrippedHorizontal(int i, int j, vector<vector<int>> cellsToMove);

    void handleStrippedVertical(int i, int j, vector<vector<int>> cellsToMove);

    void handleWrapped(int i, int j, vector<vector<int>> cellsToMove, int leftDownMargin, int rightUpMargin);

    void emptyCell(int i, int j);

    void emptyCells(vector<vector<int>> cellsToEmpty) override;

    void doubleStriped(Point firstCellPosition, Point secondCellPosition, const vector<vector<int>> &cellsToMove);

    void doubleWrapped(Point firstCellPosition, Point secondCellPosition, vector<vector<int>> cellsToMove);

    void handleWrappedStripped(Point firstCellPosition, Point secondCellPosition, vector<vector<int>> cellsToMove, bool isHorizontal);

    void multiColorSpecial(Point firstCellPosition, Point secondCellPosition,
                           CandySpeciality speciality, Color color);

    bool doubleSpecialCandyInteraction(Point firstCellPosition, Point secondCellPosition, Color firstCellColor,
                                       Color secondCellColor, CandySpeciality firstCellSpeciality,
                                       CandySpeciality secondCellSpeciality);

    void normalCandyAndMulticolorInteraction(Color colorToRemove, Point multicolorPosition);

    void doubleStripedCandyInteraction(Point firstCellPosition, Point secondCellPosition);

    void stripedAndWrappedCandyInteraction(Point firstCellPosition, Point secondCellPosition);

    void doubleWrappedInteraction(Point, Point);

    void stripedMulticolorInteraction(Point, Point, Color);

    void wrappedAndMulticolorInteraction(Point, Point, Color);

    void doubleMulticolorInteraction();

    void doubleStripedOrWrappedInteraction(Point firstCellPosition, Point secondCellPosition);

    void MultiColorInteractions(Point firstCellPosition, Point secondCellPosition, Color firstColor, Color secondColor);

    void
    setInteraction(bool interacting, Color color = Color::NONE, CandySpeciality speciality = CandySpeciality::NONE);

};


#endif //TEMP_CLASSES_MATCHHANDLER_H
