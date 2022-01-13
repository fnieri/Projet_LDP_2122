/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: Animation.cpp
* Date: 13/01/2022
*/
        
#include "Animation.h"

void Animation::moveCellsDiagonally(const vector<vector<int>> &diagonalCells, int lr) {
    for (int l = 0; l < (int) margin; ++l) {
        for (auto &cellToDrop: diagonalCells) {
            int i = cellToDrop[0];
            int j = cellToDrop[1];
            Cell *toDrop = &CellsVertex[i][j];
            Point movingCenter{toDrop->getCenter().x - lr,
                               toDrop->getCenter().y + 1};
            toDrop->setCenter(movingCenter);
        }
        gameWait(4000);
    }

    int firstCol = diagonalCells[0][0];
    int firstRow = diagonalCells[0][1];
    Cell *firstCell = &CellsVertex[firstCol][firstRow];
    Cell *emptyCell = &CellsVertex[firstCol + 1][firstRow - lr];
    emptyCell->setClickable(*(firstCell->getCandy()));
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
            toReplace->setClickable(*(toDrop->getCandy()));
        } catch (out_of_range &e) {}
        if (col == 0) toReplace->setClickable(CandyFactory::generateCandy(NONE));
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
        gameWait(4000);
    }

    for (auto &cellToReplace: cellsToReplace) {
        int i = cellToReplace[0];
        int j = cellToReplace[1];
        Cell *toReplace = &CellsVertex[i][j];
        for (int k = i; k > 0; --k) {
            toReplace = &CellsVertex[k - 1][j];
            if (!isCandy(*toReplace)) {
                (&CellsVertex[k][j])->setClickable(ClickableFactory::makeEmptyCandy());
                break;
            }
            (CellsVertex)[k][j].setClickable(*(toReplace->getCandy()));
            Point originalCenter{toReplace->getCenter().x,
                                 toReplace->getCenter().y - margin};
            toReplace->setCenter(originalCenter);
        }
        // don't generate a new candy on top if last cell is not a candy
        if (isCandy(toReplace)) {
            Cell *topCell = &CellsVertex[0][j];
            topCell->setClickable(ClickableFactory::makeCandy(CandySpeciality::NONE));
        }
    }
}   


void Animation::destroyObject(Cell *cell) {
    cell->setClickable(CandyFactory::generateBoomCandy());
    usleep(70000);
    Fl::check();
}
