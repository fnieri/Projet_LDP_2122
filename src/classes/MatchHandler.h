//
// Created by louis on 19/12/2021.
//

#ifndef PROJET_LDP_2122_MATCHHANDLER_H
#define PROJET_LDP_2122_MATCHHANDLER_H


#include <game.h>
#include <candyfactory.h>

class MatchHandler : virtual public Game, virtual public CandyFactory, public Animation {
public:
    void handleStrippedHorizontal(vector <vector<Cell>> *CellVector, int i, int j,
                                         vector <vector<int>> cellsToMove);

    void handleStrippedVertical(vector <vector<Cell>> *CellVector, int i, int j,
                                       vector <vector<int>> cellsToMove);

    void handleWrapped(vector <vector<Cell>> *CellVector, int i, int j,
                              vector <vector<int>> cellsToMove, int leftDownMargin, int rightUpMargin);


    void emptyCell(vector <vector<Cell>> *CellVector, int i, int j);

    void emptyCells(vector <vector<int>> cellsToEmpty, vector <vector<Cell>> *CellVector);

    void normalCandyAndMulticolorInteraction(Color colorToRemove, Point multicolorPosition);

    void doubleStripedCandyInteraction(Point firstCellPosition, Point secondCellPosition);

    void stripedAndWrappedCandyInteraction(Point firstCellPosition, Point secondCellPosition);

    void doubleWrappedInteraction(Point, Point);

    void stripedMulticolorInteraction(Point, Point, Color);

    void wrappedAndMulticolorInteraction(Point, Point, Color);

    void doubleMulticolorInteraction();

    void doubleStripedOrWrappedInteraction(Point firstCellPosition, Point secondCellPosition, int leftOffset,
                                           int rightOffset);

    void MultiColorInteractions(Point firstCellPosition, Point secondCellPosition, Color firstColor, Color secondColor,
                                vector <CandySpeciality> specialities);

};


#endif //PROJET_LDP_2122_MATCHHANDLER_H
