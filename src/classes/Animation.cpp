//
// Created by louis on 19/12/2021.
//

#include "Animation.h"

void Animation::moveCellsDown(vector <vector<int>> cellsToReplace) {

    emptyCells(cellsToReplace);

    for (int l = 0; l < (int) margin; ++l) {
        for (auto &cellToReplace: cellsToReplace) {
            
            int i = cellToReplace[0];
            int j = cellToReplace[1];
            // drops all candy one cell under then generates candy for top cell
            for (int k = i; k > 0; --k) {
                Point movingCenter{(CellsVertex)[k - 1][j].getCenter().x,
                                (CellsVertex)[k - 1][j].getCenter().y + 1};
                (CellsVertex)[k - 1][j].setCenter(movingCenter);
            }
        }
    Fl::wait(0.003);
    }

    for (auto &cellToReplace: cellsToReplace) {
        int i = cellToReplace[0];
        int j = cellToReplace[1];
        for (int k = i; k > 0; k--) {
            if (isCandy(CellsVertex[k-1][j])) {
                (CellsVertex)[k][j].setObject(*(CellsVertex)[k - 1][j].getCandy());
                Point originalCenter{(CellsVertex)[k - 1][j].getCenter().x,
                                    (CellsVertex)[k - 1][j].getCenter().y - margin};
                (CellsVertex)[k - 1][j].setCenter(originalCenter);
            }    
        }
        (CellsVertex)[0][j].setObject(ClickableFactory::makeCandy(CandySpeciality::NONE));
    }
}

void Animation::destroyObject(Cell *cell) {
    vector <Fl_Color> colors = {FL_LIGHT2, FL_LIGHT1, FL_BLACK, FL_LIGHT3};
    cell->setHighlighted(true);
    for (auto color: colors) {
        cell->setHighlightColor(color);

        Fl::wait(0.1);
    }
    cell->setHighlighted(false);
    cell->setHighlightColor(FL_LIGHT3);
}