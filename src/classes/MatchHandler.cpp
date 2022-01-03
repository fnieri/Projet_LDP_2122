//
// Created by louis on 19/12/2021.
//

#include "MatchHandler.h"

// to prevent bugs:  switch from a vector of vector of int to a vector of cell*
// also need to handle Multicolor destruction in handleCellsToReplace

void MatchHandler::handleCellsToReplace(vector<vector<int>> cellsToReplace) {
    vector<vector<int>> specialCells;
    for (auto &cell: cellsToReplace) {
        CandySpeciality speciality = CellsVertex[cell[0]][cell[1]].getSpeciality();
        Color color = CellsVertex[cell[0]][cell[1]].getColor();
        if (speciality != NONE) {
            if (interactionColor != color && interactionSpeciality != speciality) {
                specialCells.push_back(cell);
            }
        } else if (!CellsVertex[cell[0]][cell[1]].isEmpty()) {
            emptyCell(cell[0], cell[1]);
        }
    }
    int i = 0;
    for (auto &cellToReplace: specialCells) {
        CandySpeciality cellSpeciality = CellsVertex[cellToReplace[0]][cellToReplace[1]].getSpeciality();
        emptyCell(cellToReplace[0], cellToReplace[1]);
        vector<vector<int>> recursiveVector = {cellsToReplace.begin() + i, cellsToReplace.end()};
        switch (cellSpeciality) {
            case STRIPED_VERTICAL: {
                handleStrippedVertical(cellToReplace[0], cellToReplace[1], recursiveVector);
                return;
            }
            case STRIPED_HORIZONTAL: {
                handleStrippedHorizontal(cellToReplace[0], cellToReplace[1], recursiveVector);
                return;
            }
            case BOMB: {
                handleWrapped(cellToReplace[0], cellToReplace[1], recursiveVector, -1, 1);
                return;
            }
            case MULTICOLOR: {
                // TODO: handle multicolor in case it gets destroyed by a special candy
                break;
            }
            default: {
                break;
            }
        }
        ++i;
    }
    vector<vector<int>> cellsToDrop;
    // find all empty cells in CellsVertex and drop them
    for (int col = 0; col < (int) CellsVertex.size(); ++col) {
        for (int row = 0; row < (int) CellsVertex[col].size(); ++row) {
            if (CellsVertex[col][row].isEmpty()) {
                cellsToDrop.push_back({col, row});
            }
        }
    }
    moveCellsDown(cellsToDrop);
//    moveCellsDown(cellsToReplace);
}


void MatchHandler::handleStrippedHorizontal(int i, int j, vector<vector<int>> cellsToMove) {
//    cellsToMove.push_back({i, j});
    for (int k = 0; k < (int) CellsVertex[i].size(); ++k) {
        vector<int> cellToMove = {i, k};
        if (find(cellsToMove.begin(), cellsToMove.end(), cellToMove) == cellsToMove.end()) {
            cellsToMove.push_back(cellToMove);
        }
    }
    handleCellsToReplace(cellsToMove);
}

void MatchHandler::handleStrippedVertical(int i, int j,
                                          vector<vector<int>> cellsToMove) {
//    cellsToMove.push_back({i, j});
    for (int k = 0; k < (int) CellsVertex.size(); ++k) {
        vector<int> cellToMove = {k, j};
        cellsToMove.push_back(cellToMove);
//        if (find(cellsToMove.begin(), cellsToMove.end(), cellToMove) == cellsToMove.end()) {
//        }
    }
    handleCellsToReplace(cellsToMove);
}

void
MatchHandler::handleWrapped(int i, int j, vector<vector<int>> cellsToMove, int leftDownMargin, int rightUpMargin) {
    for (int k = leftDownMargin; k <= rightUpMargin; ++k) {
        for (int l = leftDownMargin; l <= rightUpMargin; ++l) {
            vector<int> cellToMove = {i + k, j + l};
            if ((i + k >= 0 && i + k < (int) CellsVertex[i].size()) &&
                (j + l >= 0 && j + l < (int) CellsVertex[j].size())) {
                if (find(cellsToMove.begin(), cellsToMove.end(), cellToMove) == cellsToMove.end()) {
                    cellsToMove.push_back(cellToMove);
                }
            }
        }
    }
    handleCellsToReplace(cellsToMove);
}

void
MatchHandler::handleWrappedStripped(Point firstCellPosition, Point secondCellPosition, vector<vector<int>> cellsToMove,
                                    bool isHorizontal) {
    vector<vector<int>> cellsToEmpty = {{firstCellPosition.x,  firstCellPosition.y},
                                        {secondCellPosition.x, secondCellPosition.y}};
    emptyCells(cellsToEmpty);
    int i = firstCellPosition.x;
    int j = firstCellPosition.y;
    for (int l = -1; l < 2; ++l) {
        for (int k = 0; k < (int) CellsVertex[i].size(); ++k) {
            vector<int> cellToMove;
            if (isHorizontal) {
//                if (l == 0 && k == j) {
//                    continue;
//                }
                cellToMove = {i + l, k};
                if (find(cellsToMove.begin(), cellsToMove.end(), cellToMove) == cellsToMove.end()) {
                    cellsToMove.push_back(cellToMove);
                }
            } else {
                cellToMove = {k, j + l};
                cellsToMove.push_back(cellToMove);
            }
        }
    }
    handleCellsToReplace(cellsToMove);
}

void MatchHandler::emptyCell(int i, int j) {
    destroyCandy(&CellsVertex[i][j]);
    CellsVertex[i][j].setCandy(generateEmptyCandy());
}

void MatchHandler::emptyCells(vector<vector<int>> cellsToEmpty) {
    for (auto &cellToEmpty: cellsToEmpty)
        emptyCell(cellToEmpty[0], cellToEmpty[1]);
}

void
MatchHandler::doubleStriped(Point firstCellPosition, Point secondCellPosition, const vector<vector<int>> &cellsToMove) {
    handleStrippedHorizontal(firstCellPosition.x, firstCellPosition.y, cellsToMove);
    handleStrippedVertical(secondCellPosition.x, secondCellPosition.y, cellsToMove);
}

void MatchHandler::doubleWrapped(Point firstCellPosition, Point secondCellPosition, vector<vector<int>> cellsToMove) {
    handleWrapped(firstCellPosition.x, firstCellPosition.y, std::move(cellsToMove), -2, 2);
}

void MatchHandler::multiColorSpecial(Point firstCellPosition, Point secondCellPosition,
                                     CandySpeciality speciality, Color color) {
    vector<Cell *> cellsToDestroy;
    cellsToDestroy.push_back(&CellsVertex[firstCellPosition.x][firstCellPosition.y]);
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            switch (speciality) {
                case CandySpeciality::NONE: {
                    if (CellsVertex[i][j].getColor() == color) {
                        cellsToDestroy.push_back(&CellsVertex[i][j]);
                        break;
                    }
                }
                case CandySpeciality::STRIPED_HORIZONTAL:
                case CandySpeciality::STRIPED_VERTICAL: {
                    if (CellsVertex[i][j].getColor() == color) {
                        //Choose randomly between striped horizontal and vertical
                        setCellAt(static_cast<CandySpeciality>(rand() % 2 + 1), color, i, j);
                        cellsToDestroy.push_back(&CellsVertex[i][j]);
                        break;
                    }
                }
                case CandySpeciality::BOMB: {
                    if (CellsVertex[i][j].getColor() == color) {
                        setCellAt(CandySpeciality::BOMB, color, i, j);
                        cellsToDestroy.push_back(&CellsVertex[i][j]);
                        break;
                    }
                }
                default:
                    break;
            }
            Fl::check();
            usleep(3000);
        }
    }

    // i have to do this horror because cells can happen to drop down so the position isn't accurate anymore
    // i think if i apply this everywhere, candies won't disappear anymore
    for (auto &cell: cellsToDestroy) {
        for (int i = 0; i < (int) CellsVertex.size(); i++) {
            for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
                if (&CellsVertex[i][j] == cell) {
                    handleCellsToReplace(vector<vector<int>>({{i, j}}));
                    break;
                }
            }
        }
    }
}

bool
MatchHandler::doubleSpecialCandyInteraction(Point firstCellPosition, Point secondCellPosition, Color firstCellColor,
                                            Color secondCellColor, CandySpeciality firstCellSpeciality,
                                            CandySpeciality secondCellSpeciality) {
    vector<vector<int>> cellsToMove;
    switch (firstCellSpeciality) {
        case CandySpeciality::NONE:
            return false;
        case CandySpeciality::MULTICOLOR: {
            if (secondCellSpeciality == CandySpeciality::MULTICOLOR) {
                doubleMulticolorInteraction();
                return true;
            } else {
                multiColorSpecial(firstCellPosition, secondCellPosition,
                                  secondCellSpeciality, secondCellColor);
                return true;
            }
        }
        case CandySpeciality::STRIPED_HORIZONTAL:
        case CandySpeciality::STRIPED_VERTICAL: {
            switch (secondCellSpeciality) {
                case CandySpeciality::STRIPED_HORIZONTAL:
                case CandySpeciality::STRIPED_VERTICAL: {
                    doubleStriped(firstCellPosition, secondCellPosition, cellsToMove);
                    return true;
                }
                case CandySpeciality::BOMB: {
                    bool isHorizontal = firstCellSpeciality == CandySpeciality::STRIPED_HORIZONTAL;
                    handleWrappedStripped(firstCellPosition, secondCellPosition, std::move(cellsToMove), isHorizontal);
                    return true;
                }
                default:
                    break;
            }
        }
        case CandySpeciality::BOMB: {
            switch (secondCellSpeciality) {
                case CandySpeciality::BOMB: {
                    doubleWrapped(firstCellPosition, secondCellPosition, cellsToMove);
                    return true;
                }
                default:
                    break;
            }
        }
        default: {
            break;
        }
    }

    return false;
}


void MatchHandler::doubleMulticolorInteraction() {
    reset();
}

// need to do more checks but i think we dont need this
void MatchHandler::setInteraction(bool interacting, Color color, CandySpeciality speciality) {
    if (interacting) {
        isInteracting = true;
        interactionColor = color;
        interactionSpeciality = speciality;
    } else {
        isInteracting = false;
        interactionColor = Color::NONE;
        interactionSpeciality = CandySpeciality::NONE;
    }
}