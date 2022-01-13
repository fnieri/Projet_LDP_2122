/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: MatchHandler.cpp
* Date: 13/01/2022
*/
        
#include "MatchHandler.h"

void MatchHandler::handleCellsToReplace(vector <vector<int>> cellsToReplace) {
    vector <vector<int>> specialCells;
    for (auto &cell: cellsToReplace) {
        Cell currentCell = CellsVertex[cell[0]][cell[1]];
        decreaseObjective(currentCell);
        
        if (isCandy(currentCell)) {
            CandySpeciality speciality = currentCell.getSpeciality();
            Color color = currentCell.getColor();
            sendSpecialityScore(speciality);
            
            if (speciality != NONE) {
                if (interactionColor != color && interactionSpeciality != speciality) {
                    specialCells.push_back(cell);
                }
            } else if (!CellsVertex[cell[0]][cell[1]].isEmpty()) {
                emptyCell(cell[0], cell[1]);
            }
        }

        else if (isIcing(currentCell)) {
            //Icing case will be taken care of in emptyCell
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
    handleGravity();
}

void MatchHandler::handleGravity() {
    vector<vector<int>> cellsToDrop = findEmptyCells();
    moveCellsDown(cellsToDrop);
    if (remainingEmptyCells()) {
        handleDiagonalCells();
    }
}


vector<vector<int>> MatchHandler::getDiagonalCells(int col, int row, int lr) {
    vector<vector<int>> diagonalCells;
    int i = 1;
    for (int dCol = col - 1; dCol > -1; --dCol) {
        try {
            int dRow = row + lr * i;
            Cell *checkCell = &CellsVertex.at(dCol).at(dRow);
            if (!isCandy(checkCell) || checkCell->isEmpty()) break;
            diagonalCells.push_back({dCol, dRow});
        } catch (const std::out_of_range &oor) {
            break;
        }
        ++i;
    }
    return diagonalCells;
}


bool MatchHandler::handleDiagonalCells() {
    vector<vector<int>> emptyCells = findEmptyCells();
    for (auto &cell: emptyCells) {
        int col = cell[0];
        int row = cell[1];
        for (int lr = -1; lr < 2; lr += 2) {
            try {
                Cell *checkCell = &CellsVertex.at(col - 1).at(row + lr);
                if (!isCandy(*checkCell) || checkCell->isEmpty()) continue;
                vector<vector<int>> diagonalCells = getDiagonalCells(col, row, lr);
                if (!diagonalCells.empty()) {
                    Animation::moveCellsDiagonally(diagonalCells, lr);
                    handleGravity();
                    while (checkMatches());
                    return true;
                }
            } catch (const out_of_range &e) {}
        }
    }
    return false;
}

void MatchHandler::clearIcing(int i, int j) {
    Cell* currentCell = &CellsVertex[i][j];
    IcingStatus status = currentCell->getStatus();
    sendIcingScore(status);
            
    if (status == COMPLETE_ICING)
        currentCell->setClickable(ClickableFactory::makeIcing(HALF_ICING));
    else if (status == HALF_ICING) {
        decreaseObjective(*currentCell);
        currentCell->setClickable(ClickableFactory::makeEmptyCandy());       
    }
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
    int verticalLimit = CellsVertex[i].size();
    int horizontalLimit = CellsVertex[j].size();
    for (int k = leftDownMargin; k <= rightUpMargin; ++k) {
        for (int l = leftDownMargin; l <= rightUpMargin; ++l) {
            vector<int> cellToMove = {i + k, j + l};
            if (wrappedInRange(i, j, k, l, verticalLimit, horizontalLimit)) {
                if (find(cellsToMove.begin(), cellsToMove.end(), cellToMove) == cellsToMove.end()) {
                    cellsToMove.push_back(cellToMove);
                }
            }
        }
    }
    handleCellsToReplace(cellsToMove);
}


bool MatchHandler::wrappedInRange(int i, int j, int partialVerticalOffset, int partialHorizontalOffset, int verticalLimit, int horizontalLimit) {
    int totalVerticalOffset = i + partialVerticalOffset;
    int totalHorizontalOffset = j + partialHorizontalOffset;
    return ((totalVerticalOffset >= 0 && totalVerticalOffset < verticalLimit) && 
        (totalHorizontalOffset >= 0 && totalHorizontalOffset < horizontalLimit));
}

void MatchHandler::emptyCell(int i, int j) {
    
    if (!isInputAllowed()) 
        destroyObject(&CellsVertex[i][j]);
    
    if (isCandy(CellsVertex[i][j])) {
        CellsVertex[i][j].setClickable(ClickableFactory::makeEmptyCandy());
    }
    else if (isIcing(CellsVertex[i][j])) {
        clearIcing(i, j);
    }
    

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
                clearIcing(dx, dy); 
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
    vector<Candy *> candyToDestroy;
    handleCellsToReplace(vector<vector<int>>({{firstCellPosition.x, secondCellPosition.y}}));
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (isCandy(CellsVertex[i][j])) {
                switch (speciality) {
                    case CandySpeciality::NONE: {
                        if (CellsVertex[i][j].getColor() == color) {
                            candyToDestroy.push_back(CellsVertex[i][j].getCandy());
                            break;
                        }
                    }
                    case CandySpeciality::STRIPED_HORIZONTAL:
                    case CandySpeciality::STRIPED_VERTICAL: {
                        if (CellsVertex[i][j].getColor() == color) {
                            //Choose randomly between striped horizontal and vertical
                            setCellAt(static_cast<CandySpeciality>(rand() % 2 + 1), color, i, j);
                            candyToDestroy.push_back(CellsVertex[i][j].getCandy());
                      
                            break;
                        }
                    }
                    case CandySpeciality::BOMB: {
                        if (CellsVertex[i][j].getColor() == color) {
                            setCellAt(CandySpeciality::BOMB, color, i, j);
                            candyToDestroy.push_back(CellsVertex[i][j].getCandy());
                            break;
                        }
                    }
                    default:
                        break;
                }
            }
            //gameWait(3000);
        }
    }

    // i have to do this horror because cells can happen to drop down so the position isn't accurate anymore
    // i think if i apply this everywhere, candies won't disappear anymore
    for (auto &candy: candyToDestroy) {
        for (int i = 0; i < (int) CellsVertex.size(); i++) {
            for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
                if (CellsVertex[i][j].getCandy() == candy) {
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
    sendInteractionScore(STRIPED_WRAPPED);
    vector<vector<int>> cellsToEmpty = {{firstCellPosition.x,  firstCellPosition.y},
                                        {secondCellPosition.x, secondCellPosition.y}};
    emptyCells(cellsToEmpty);
    int i = firstCellPosition.x;
    int j = firstCellPosition.y;
    for (int o = 0; o < 2; ++o) {
        for (int l = -1; l < 2; ++l) {
            for (int k = 0; k < (int) CellsVertex[i].size(); ++k) {
                vector<int> cellToMove;
                if (o) {
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
    sendInteractionScore(DOUBLE_STRIPED);
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

            destroyObject(&CellsVertex[i][j]);
            emptyCell(i,j);
            
        }
    }
    reset();
}

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