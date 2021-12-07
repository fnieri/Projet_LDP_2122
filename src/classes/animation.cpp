#include "animation.h"

Animation::Animation() = default;

void Animation::handleStrippedHorizontal(Board *board, vector<vector<Cell>> *CellVector, int i, int j,
                                         vector<vector<int>> cellsToMove) {
    for (int k = 0; k < (int) (*CellVector)[i].size(); ++k) {
        cellsToMove.push_back({i, k});
    }
    emptyCells(cellsToMove, CellVector);
    board->moveCells(cellsToMove);
}

void Animation::handleStrippedVertical(Board *board, vector<vector<Cell>> *CellVector, int i, int j,
                                       vector<vector<int>> cellsToMove) {
    for (int k = 0; k < (int) (*CellVector)[i].size(); ++k) {
        cellsToMove.push_back({k, j});
    }
    emptyCells(cellsToMove, CellVector);
    board->moveCells(cellsToMove);
}

void Animation::handleWrapped(Board *board, vector<vector<Cell>> *CellVector, int i, int j,
                              vector<vector<int>> cellsToMove) {
    for (int k = -1; k < 2; ++k) {
        for (int l = -1; l < 2; ++l) {
            cellsToMove.push_back({i + k, j + l});
        }
    }
    emptyCells(cellsToMove, CellVector);
    board->moveCells(cellsToMove);
}

void Animation::emptyCell(vector<vector<Cell>> *CellVector, int i, int j) {
    (*CellVector)[i][j].setCandy(CandyFactory::generateEmptyCandy());
}

void Animation::emptyCells(vector<vector<int>> cellsToEmpty, vector<vector<Cell>> *CellVector) {
    for (auto &cellToEmpty: cellsToEmpty)
        emptyCell(CellVector, cellToEmpty[0], cellToEmpty[1]);
}

void Animation::moveCellsDown(Board *board, vector<vector<int>> cellsToReplace, vector<vector<Cell>> *CellVector,
                              int margin) {
    for (auto &cellToReplace: cellsToReplace) {
        CandySpeciality cellSpeciality = (*CellVector)[cellToReplace[0]][cellToReplace[1]].getSpeciality();
        switch (cellSpeciality) {
            case CandySpeciality::STRIPED_VERTICAL:
                handleStrippedVertical(board, CellVector, cellToReplace[0], cellToReplace[1], cellsToReplace);
                return;
            case CandySpeciality::STRIPED_HORIZONTAL:
                handleStrippedHorizontal(board, CellVector, cellToReplace[0], cellToReplace[1], cellsToReplace);
                return;
            case CandySpeciality::BOMB:
                handleWrapped(board, CellVector, cellToReplace[0], cellToReplace[1], cellsToReplace);
                return;
            case CandySpeciality::MULTICOLOR:
//                emptyCell(CellVector, cellToReplace[0], cellToReplace[1]);
                break;
            case CandySpeciality::NONE:
                emptyCell(CellVector, cellToReplace[0], cellToReplace[1]);
                break;
        }
    }

    for (int l = 0; l < (int) margin; ++l) {
        for (auto &cellToReplace: cellsToReplace) {
            int i = cellToReplace[0];
            int j = cellToReplace[1];
            // drops all candy one cell under then generates candy for top cell
            for (int k = i; k > 0; k--) {
                Point movingCenter{(*CellVector)[k - 1][j].getCenter().x,
                                   (*CellVector)[k - 1][j].getCenter().y + 1};
                (*CellVector)[k - 1][j].setCenter(movingCenter);
            }
        }
        Fl::wait(0.003);
    }

    for (auto &cellToReplace: cellsToReplace) {
        int i = cellToReplace[0];
        int j = cellToReplace[1];
        for (int k = i; k > 0; k--) {
            Point originalCenter{(*CellVector)[k - 1][j].getCenter().x,
                                 (*CellVector)[k - 1][j].getCenter().y - margin};
            (*CellVector)[k - 1][j].setCenter(originalCenter);
            (*CellVector)[k][j].setCandy((*CellVector)[k - 1][j].getCandy());
        }
        (*CellVector)[0][j].setCandy(CandyFactory::generateCandy(CandySpeciality::NONE));
    }
}
