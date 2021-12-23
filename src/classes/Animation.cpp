//
// Created by louis on 19/12/2021.
//

#include "Animation.h"

// still need to handle candy speciality
void Animation::moveCellsDown(vector <vector<int>> cellsToReplace) {
//    for (auto &cellToReplace: cellsToReplace) {
//        CandySpeciality cellSpeciality = CellsVertex[cellToReplace[0]][cellToReplace[1]].getSpeciality();
//        switch (cellSpeciality) {
//            case CandySpeciality::STRIPED_VERTICAL:
//                handleStrippedVertical(cellToReplace[0], cellToReplace[1], cellsToReplace);
//                return;
//            case CandySpeciality::STRIPED_HORIZONTAL:
//                handleStrippedHorizontal(cellToReplace[0], cellToReplace[1], cellsToReplace);
//                return;
//            case CandySpeciality::BOMB:
//                handleWrapped(cellToReplace[0], cellToReplace[1], cellsToReplace, -1, 1);
//                return;
//            case CandySpeciality::MULTICOLOR:
////                emptyCell(CellVertex, cellToReplace[0], cellToReplace[1]);
//                break;
//            case CandySpeciality::NONE:
////                emptyCell(CellVertex, cellToReplace[0], cellToReplace[1]);
//                break;
//        }
//    }

    emptyCells(cellsToReplace);

    for (int l = 0; l < (int) margin; ++l) {
        for (auto &cellToReplace: cellsToReplace) {
            int i = cellToReplace[0];
            int j = cellToReplace[1];
            // drops all candy one cell under then generates candy for top cell
            for (int k = i; k > 0; k--) {
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
            (CellsVertex)[k][j].setObject(*(CellsVertex)[k - 1][j].getCandy());
            Point originalCenter{(CellsVertex)[k - 1][j].getCenter().x,
                                 (CellsVertex)[k - 1][j].getCenter().y - margin};
            (CellsVertex)[k - 1][j].setCenter(originalCenter);
        }
        (CellsVertex)[0][j].setObject(generateCandy(CandySpeciality::NONE));
    }
}