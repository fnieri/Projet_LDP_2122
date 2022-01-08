//
// Created by louis on 19/12/2021.
//

#include "Animation.h"

void Animation::moveCellsDiagonaly() {
    for (int col = (int) CellsVertex.size() - 1; col > -1; --col) {
        for (int row = 0; row < (int) CellsVertex[col].size() - 1; ++row) {
            Cell *toDrop = &CellsVertex[col][row];
            if (!toDrop->isEmpty() && toDrop->isCandy()) {
                try {
                    for (int lr = -1; lr < 2; lr += 2) {
                        Cell *toReplace = &CellsVertex.at(col + 1).at(row + lr);
                        if (toReplace->isEmpty()) {
                            for (int l = 0; l < (int) margin; ++l) {
                                Point movingCenter{toDrop->getCenter().x + 1 * lr,
                                                   toDrop->getCenter().y + 1};
                                toDrop->setCenter(movingCenter);
                                if (!isInputAllowed()) {
                                    usleep(7000);
                                    Fl::check();
                                }
                            }
                            toReplace->setObject(*(toDrop->getCandy()));
                            Point originalCenter{toDrop->getCenter().x - margin * lr,
                                                 toDrop->getCenter().y - margin};
                            toDrop->setCenter(originalCenter);
                            toDrop->setObject(ClickableFactory::makeEmptyCandy());
                            Fl::check();
                        }
                    }
                } catch (const std::out_of_range &e) {
                    continue;
                }
            }
        }
    }
}

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
        if (!isInputAllowed()) {
            usleep(7000);
            Fl::check();
        }
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
    moveCellsDiagonaly();
}

void Animation::destroyObject(Cell *cell) {
    cell->setObject(CandyFactory::generateBoomCandy());
    Fl::check();
    usleep(70000);
}
