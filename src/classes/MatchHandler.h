//
// Created by louis on 19/12/2021.
//

#ifndef TEMP_CLASSES_MATCHHANDLER_H
#define TEMP_CLASSES_MATCHHANDLER_H

#include "Animation.h"
#include "ClickableFactory.h"
#include "ScoreCalculator.h"
#include "Enums/Interaction.h"
#include "GameObjective.h"

class MatchHandler : public Animation, public GameObjective {
public:
    void handleCellsToReplace(vector <vector<int>> cellsToReplace);

    void handleStrippedHorizontal(int i, int j, vector <vector<int>> cellsToMove);

    void handleStrippedVertical(int i, int j, vector <vector<int>> cellsToMove);

    void handleWrapped(int i, int j, vector <vector<int>> cellsToMove, int leftDownMargin, int rightUpMargin);

    void emptyCell(int i, int j);

    void emptyCells(vector<vector<int>> cellsToEmpty) override;

    void normalCandyAndMulticolorInteraction(Color colorToRemove, Point multicolorPosition);

    void doubleStripedCandyInteraction(Point firstCellPosition, Point secondCellPosition);

    void stripedAndWrappedCandyInteraction(Point firstCellPosition, Point secondCellPosition);

    void doubleWrappedInteraction(Point, Point);

    void doubleMulticolorInteraction();

    void doubleStripedOrWrappedInteraction(Point firstCellPosition, Point secondCellPosition, int leftOffset,
                                           int rightOffset);

    void MultiColorInteractions(Point firstCellPosition, Point secondCellPosition, Color firstColor, Color secondColor,
                                vector <CandySpeciality> specialities);

    void sendInteractionScore(Interaction);

    void sendScoreMulticolor(CandySpeciality);

    void sendIcingScore(IcingStatus);

    void sendSpecialityScore(CandySpeciality);

};



#endif //TEMP_CLASSES_MATCHHANDLER_H
