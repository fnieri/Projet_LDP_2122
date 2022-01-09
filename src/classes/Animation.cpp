//
// Created by louis on 19/12/2021.
//

#include "Animation.h"

void Animation::moveCellsDiagonaly(const vector<vector<int>> &diagonalCells, int lr) {
    for (int l = 0; l < (int) margin; ++l) {
        for (auto &cellToDrop: diagonalCells) {
            int i = cellToDrop[0];
            int j = cellToDrop[1];
            Cell *toDrop = &CellsVertex[i][j];
            Point movingCenter{toDrop->getCenter().x - lr,
                               toDrop->getCenter().y + 1};
            toDrop->setCenter(movingCenter);
        }
        gameWait(7000);
    }

    int firstCol = diagonalCells[0][0];
    int firstRow = diagonalCells[0][1];
    Cell *firstCell = &CellsVertex[firstCol][firstRow];
    Cell *emptyCell = &CellsVertex[firstCol+1][firstRow-lr];
    emptyCell->setObject(*(firstCell->getCandy()));
    for (int k = 0; k < (int) diagonalCells.size(); ++k) {
        int col = diagonalCells[k][0];
        int row = diagonalCells[k][1];
        Cell *toReplace = &CellsVertex[col][row];
        Point originalCenter{toReplace->getCenter().x + margin * lr,
                             toReplace->getCenter().y - margin};
        toReplace->setCenter(originalCenter);
        try {
            int dCol = diagonalCells.at(k + 1)[0];
            int dRow = diagonalCells.at(k + 1)[1];
            Cell *toDrop = &CellsVertex[dCol][dRow];
            toReplace->setObject(*(toDrop->getCandy()));
        } catch (out_of_range &e) {}
            if (col == 0) toReplace->setObject(CandyFactory::generateCandy(NONE));
    }
//    for (auto &cellToDrop: diagonalCells) {
//        int i = cellToDrop[0];
//        int j = cellToDrop[1];
//        int ri = i - 1;
//        int rj = j - lr;
//        try {
//            Cell *toDrop = &CellsVertex.at(i).at(j);
//            Cell *toReplace = &CellsVertex.at(ri).at(rj);
//
//            toReplace->setObject(*(toReplace->getCandy()));
//            Point originalCenter{toDrop->getCenter().x - margin * lr,
//                                 toDrop->getCenter().y - margin};
//            toDrop->setCenter(originalCenter);
////            if (i == 0) toDrop->setObject(ClickableFactory::generateCandy(NONE));
//        } catch (const std::out_of_range &e) {}
//    }
//    for_each(diagonalCells.rbegin(), diagonalCells.rend(), [&](auto &cellToDrop) {
//        int i = cellToDrop[0];
//        int j = cellToDrop[1];
//        int ri = cellToDrop[0] + 1;
//        int rj = cellToDrop[1] + 1 * lr;
//        try {
//            Cell *toDrop = &CellsVertex.at(i).at(j);
//            Cell *toReplace = &CellsVertex.at(ri).at(rj);
//            toReplace->setObject(*(toDrop->getCandy()));
//            Point originalCenter{toDrop->getCenter().x + margin * lr,
//                                 toDrop->getCenter().y - margin};
//            if (i == 0) toDrop->setObject(ClickableFactory::generateCandy(NONE));
//            toDrop->setCenter(originalCenter);
//        } catch (const std::out_of_range &e) {}
//    });
}

//void Animation::moveCellsDiagonaly() {
//    for (int lr = -1; lr < 2; lr += 2) {
//        vector<vector<int>> cellsToDrop;
//        for (int col = (int) CellsVertex.size() - 1; col > -1; --col) {
//            for (int row = 0; row < (int) CellsVertex[col].size() - 1; ++row) {
//                Cell *toDrop = &CellsVertex[col][row];
//                if (!toDrop->isEmpty() && toDrop->isCandy()) {
//                    try {
//                        Cell *toReplace = &CellsVertex.at(col + 1).at(row + lr);
//                        if (toReplace->isEmpty()) {
//                            for (int k = col; k > -1; --k) {
//                                try {
//                                    int dCol = col - k;
//                                    int dRow = row - k * lr;
//                                    Cell *diagonalCell = &CellsVertex.at(dCol).at(dRow);
//                                    if (!diagonalCell->isCandy()) continue;
//                                    cellsToDrop.push_back({dCol, dRow});
//                                } catch (const std::out_of_range &e) {
//                                    break;
//                                }
//                            }
//                        }
//                    } catch (const std::out_of_range &e) {
//                        break;
//                    }
//                }
//            }
//        }
//
//        for (int l = 0; l < (int) margin; ++l) {
//            for (auto &cellToDrop: cellsToDrop) {
//                int i = cellToDrop[0];
//                int j = cellToDrop[1];
//                Cell *toDrop = &CellsVertex[i][j];
//                Point movingCenter{toDrop->getCenter().x + lr,
//                                   toDrop->getCenter().y + 1};
//                toDrop->setCenter(movingCenter);
//            }
//            gameWait(7000);
//        }
//        for_each(cellsToDrop.rbegin(), cellsToDrop.rend(), [&](auto &cellToDrop) {
//            int i = cellToDrop[0];
//            int j = cellToDrop[1];
//            int ri = cellToDrop[0] + 1;
//            int rj = cellToDrop[1] + 1 * lr;
//            try {
//                Cell *toDrop = &CellsVertex.at(i).at(j);
//                Cell *toReplace = &CellsVertex.at(ri).at(rj);
//                toReplace->setObject(*(toDrop->getCandy()));
//                Point originalCenter{toDrop->getCenter().x - margin * lr,
//                                     toDrop->getCenter().y - margin};
//                if (i == 0) toDrop->setObject(ClickableFactory::generateCandy(NONE));
//                toDrop->setCenter(originalCenter);
//            } catch (const std::out_of_range &e) {
//            }
//        });
//        while (checkMatches());
//    }
//}


void Animation::moveCellsDown(vector<vector<int>> cellsToReplace) {
    for (int l = 0; l < (int) margin; ++l) {
        for (auto &cellToReplace: cellsToReplace) {
            int i = cellToReplace[0];
            int j = cellToReplace[1];
            // drops all candy one cell under then generates candy for top cell
            for (int k = i; k > 0; --k) {
                Cell *toDrop = &CellsVertex[k - 1][j];
                if (!isCandy(toDrop)) break;

                Point movingCenter{toDrop->getCenter().x,
                                   toDrop->getCenter().y + 1};
                toDrop->setCenter(movingCenter);
            }
        }
        // TODO: change this to function in game and use it everywhere
        gameWait(7000);
    }

    for (auto &cellToReplace: cellsToReplace) {
        int i = cellToReplace[0];
        int j = cellToReplace[1];
        Cell *toReplace = &CellsVertex[i][j];
        for (int k = i; k > 0; --k) {
            toReplace = &CellsVertex[k - 1][j];
            if (!isCandy(*toReplace)) {
                (&CellsVertex[k][j])->setObject(ClickableFactory::makeEmptyCandy());
                break;
            }
            (CellsVertex)[k][j].setObject(*(toReplace->getCandy()));
            Point originalCenter{toReplace->getCenter().x,
                                 toReplace->getCenter().y - margin};
            toReplace->setCenter(originalCenter);
        }
        // don't generate a new candy on top if last cell is not a candy
        if (toReplace->isCandy()) {
            Cell *topCell = &CellsVertex[0][j];
            topCell->setObject(ClickableFactory::makeCandy(CandySpeciality::NONE));
        }
    }
//    if (remainingEmptyCells()) {
////        cout << "remaining empty cells" << endl;
//        moveCellsDiagonaly();
//
//    }
}

void Animation::destroyObject(Cell *cell) {
    cell->setObject(CandyFactory::generateBoomCandy());
    usleep(70000);
    Fl::check();
}
