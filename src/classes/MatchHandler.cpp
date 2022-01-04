//
// Created by louis on 19/12/2021.
//

#include "MatchHandler.h"

void MatchHandler::handleCellsToReplace(vector <vector<int>> cellsToReplace) {

    vector <vector<int>> specialCells;
    for (auto &cell: cellsToReplace) {
        Cell currentCell = CellsVertex[cell[0]][cell[1]];
        decreaseObjective(currentCell);
        
        if (isCandy(currentCell)) {
            CandySpeciality speciality = CellsVertex[cell[0]][cell[1]].getSpeciality();
            Color color = CellsVertex[cell[0]][cell[1]].getColor();
            sendSpecialityScore(speciality);
            
            if (speciality != NONE) 
                specialCells.push_back(cell);
            else 
                emptyCell(cell[0], cell[1]);
        }

        else if (isIcing(currentCell)) {
            IcingStatus status = currentCell.getStatus();
            sendIcingScore(status);
            
            if (status == COMPLETE_ICING) 
                currentCell.setObject(ClickableFactory::generateIcing(HALF_ICING));
            else 
                emptyCell(cell[0], cell[1]);
        }
    }

    int i = 0;
    for (auto &cellToReplace: specialCells) {
        CandySpeciality cellSpeciality = CellsVertex[cellToReplace[0]][cellToReplace[1]].getSpeciality();
        emptyCell(cellToReplace[0], cellToReplace[1]);
        vector <vector<int>> recursiveVector = {cellsToReplace.begin() + i, cellsToReplace.end()};
        switch (cellSpeciality) {
            case STRIPED_VERTICAL: {
                handleStripedVertical(cellToReplace[0], cellToReplace[1], recursiveVector);
                return;
            }
            case STRIPED_HORIZONTAL: {
                handleStripedHorizontal(cellToReplace[0], cellToReplace[1], recursiveVector);
                return;
            }
            case BOMB: {
                handleWrapped(cellToReplace[0], cellToReplace[1], recursiveVector, -1, 1);
                return;
            }
            case MULTICOLOR: {
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

    moveCellsDown(cellsToReplace);
}



void MatchHandler::handleStripedHorizontal(int i, int j, vector <vector<int>> cellsToMove) {
    for (int k = 0; k < (int) CellsVertex[i].size(); ++k) {
        vector<int> cellToMove = {i, k};
        if (find(cellsToMove.begin(), cellsToMove.end(), cellToMove) == cellsToMove.end()) {
            cellsToMove.push_back(cellToMove);
        }
    }
    handleCellsToReplace(cellsToMove);
}

void MatchHandler::handleStripedVertical(int i, int j,
                                          vector <vector<int>> cellsToMove) {
   for (int k = 0; k < (int) CellsVertex.size(); ++k) {
        vector<int> cellToMove = {k, j};
        cellsToMove.push_back(cellToMove);
    }
    handleCellsToReplace(cellsToMove);
}

void
MatchHandler::handleWrapped(int i, int j, vector <vector<int>> cellsToMove, int leftDownMargin, int rightUpMargin) {
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
}


bool MatchHandler::wrappedInRange(int i, int j, int partialVerticalOffset, int partialHorizontalOffset, int verticalLimit, int horizontalLimit) {
    int totalVerticalOffset = i + partialVerticalOffset;
    int totalHorizontalOffset = j + partialHorizontalOffset;
    return ((totalVerticalOffset >= 0 && totalVerticalOffset < verticalLimit) && 
        (totalHorizontalOffset >= 0 && totalHorizontalOffset < horizontalLimit));
}

void MatchHandler::emptyCell(int i, int j) {
    
    if (isCandy(CellsVertex[i][j]))
        CellsVertex[i][j].setObject(ClickableFactory::makeEmptyCandy());

    else if (isIcing(CellsVertex[i][j])) {
        if (CellsVertex[i][j].getStatus() == COMPLETE_ICING)
            CellsVertex[i][j].setObject(ClickableFactory::makeIcing(HALF_ICING));
        else
            CellsVertex[i][j].setObject(ClickableFactory::makeEmptyCandy());       
    }
    
    destroyObject(&CellsVertex[i][j]);

    vector <array<int, 2>> deltas = {{0,  1},
                                     {1,  0},
                                     {0,  -1},
                                     {-1, 0}};
    
    //Check if there are are neighboring icing cells
    for (auto d: deltas) {
        int dx = i + d[0];
        int dy = j + d[1];
        try {
            if (isIcing(CellsVertex.at(dx).at(dy))) {
                IcingStatus status = CellsVertex.at(dx).at(dy).getStatus();
                if (status == COMPLETE_ICING)
                    CellsVertex[dx][dy].setObject(ClickableFactory::makeIcing(HALF_ICING));
                else
                    CellsVertex[dx][dy].setObject(ClickableFactory::makeEmptyCandy());
            }
        } 
        catch (std::out_of_range &e) {continue;}
    }
}

void MatchHandler::emptyCells(vector <vector<int>> cellsToEmpty) {
    for (auto &cellToEmpty: cellsToEmpty)
        emptyCell(cellToEmpty[0], cellToEmpty[1]);
}


void MatchHandler::multiColorSpecial(Point firstCellPosition, Point secondCellPosition, 
                                          CandySpeciality speciality, Color color) {

    sendScoreMulticolor(speciality);
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
void
MatchHandler::handleWrappedStriped(Point firstCellPosition, Point secondCellPosition,
                                   vector<vector<int>> cellsToMove, bool isHorizontal) {
     vector<vector<int>> cellsToEmpty = {{firstCellPosition.x,  firstCellPosition.y},
                                        {secondCellPosition.x, secondCellPosition.y}};
    emptyCells(cellsToEmpty);
    int i = firstCellPosition.x;
    int j = firstCellPosition.y;
    for (int l = -1; l < 2; ++l) {
        for (int k = 0; k < (int) CellsVertex[i].size(); ++k) {
            vector<int> cellToMove;
            if (isHorizontal) {
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
                    handleWrappedStriped(firstCellPosition, secondCellPosition, std::move(cellsToMove), isHorizontal);
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

void MatchHandler::doubleWrapped(Point firstCellPosition, Point secondCellPosition, vector<vector<int>> cellsToMove) {
    sendInteractionScore(DOUBLE_WRAPPED);
    handleWrapped(firstCellPosition.x, firstCellPosition.y, cellsToMove, -2, 2);
}

void
MatchHandler::doubleStriped(Point firstCellPosition, Point secondCellPosition, const vector<vector<int>> &cellsToMove) {
    handleStripedHorizontal(firstCellPosition.x, firstCellPosition.y, cellsToMove);
    handleStripedVertical(secondCellPosition.x, secondCellPosition.y, cellsToMove);
}


void MatchHandler::sendInteractionScore(Interaction interaction) {
    addToScore(ScoreCalculator::returnInteractionScore(interaction));
}

void MatchHandler::sendScoreMulticolor(CandySpeciality speciality) {
    Interaction currentInteraction;
    switch (speciality) {
        case STRIPED_HORIZONTAL:
        case STRIPED_VERTICAL:
            currentInteraction = STRIPED_MULTICOLOR;
        case BOMB:
            currentInteraction = WRAPPED_MULTICOLOR;
        case NONE:
            currentInteraction = NONE_MULTICOLOR;
        case MULTICOLOR:
            currentInteraction = DOUBLE_MULTICOLOR;
        default:
            return;
    }
    sendInteractionScore(currentInteraction);
}


void MatchHandler::sendSpecialityScore(CandySpeciality speciality) {
    addToScore(ScoreCalculator::returnCandyScore(speciality));
}

void MatchHandler::sendIcingScore(IcingStatus status) {
    addToScore(ScoreCalculator::returnIcingScore(status));
}

void MatchHandler::doubleMulticolorInteraction() {
    sendInteractionScore(DOUBLE_MULTICOLOR);
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            //Check cell for objective
            decreaseObjective(CellsVertex[i][j]);
            
            //Calculate score for each cell
            if (isCandy(CellsVertex[i][j])) {
                sendSpecialityScore(CellsVertex[i][j].getSpeciality()); }
            else if (isIcing(CellsVertex[i][j])) {
                sendIcingScore(CellsVertex[i][j].getStatus());}
            else {}
            
            //Empty cell and animate its destruction

            emptyCell(i,j);
            destroyObject(&CellsVertex[i][j]);
            
        }
    }
    reset();
}