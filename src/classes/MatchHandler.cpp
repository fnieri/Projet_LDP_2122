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
            sendSpecialityScore(speciality);
            
            if (speciality != NONE) {
                specialCells.push_back(cell);
            } else {
                emptyCell(cell[0], cell[1]);
            }
        }

        else if (isIcing(currentCell)) {
            IcingStatus status = currentCell.getStatus();
            sendIcingScore(status);
            
            if (status == COMPLETE_ICING) {
                currentCell.setObject(ClickableFactory::generateIcing(HALF_ICING));
            } else {
                emptyCell(cell[0], cell[1]);
            }
        }
    }

    int i = 0;
    for (auto &cellToReplace: specialCells) {
        CandySpeciality cellSpeciality = CellsVertex[cellToReplace[0]][cellToReplace[1]].getSpeciality();
        emptyCell(cellToReplace[0], cellToReplace[1]);
        vector <vector<int>> recursiveVector = {cellsToReplace.begin() + i, cellsToReplace.end()};
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
                break;
            }
            default: {
                break;
            }
        }
        ++i;
    }
    
    moveCellsDown(cellsToReplace);
}



void MatchHandler::handleStrippedHorizontal(int i, int j, vector <vector<int>> cellsToMove) {
   // cellsToMove.push_back({i, j});
    for (int k = 0; k < (int) CellsVertex[i].size(); ++k) {
        vector<int> cellToMove = {i, k};
        if (find(cellsToMove.begin(), cellsToMove.end(), cellToMove) == cellsToMove.end()) {
            cellsToMove.push_back(cellToMove);
        }
    }
    handleCellsToReplace(cellsToMove);
}

void MatchHandler::handleStrippedVertical(int i, int j,
                                          vector <vector<int>> cellsToMove) {
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

void MatchHandler::emptyCell(int i, int j) {
    
    if (isCandy(CellsVertex[i][j])) {
        CellsVertex[i][j].setObject(ClickableFactory::makeEmptyCandy());
    }

    else if (isIcing(CellsVertex[i][j])) {
        if (CellsVertex[i][j].getStatus() == COMPLETE_ICING) {
            CellsVertex[i][j].setObject(ClickableFactory::makeIcing(HALF_ICING));
        }
        else {
            CellsVertex[i][j].setObject(ClickableFactory::makeEmptyCandy());       
        }
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
                if (status == COMPLETE_ICING) {
                    CellsVertex[dx][dy].setObject(ClickableFactory::makeIcing(HALF_ICING));
                }
                else {
                    CellsVertex[dx][dy].setObject(ClickableFactory::makeEmptyCandy());
                }
            }
        } 
        catch (std::out_of_range &e) {continue;}
    }
}

void MatchHandler::emptyCells(vector <vector<int>> cellsToEmpty) {
    for (auto &cellToEmpty: cellsToEmpty)
        emptyCell(cellToEmpty[0], cellToEmpty[1]);
}


void MatchHandler::MultiColorInteractions(Point firstCellPosition, Point secondCellPosition, Color firstColor,
                                          Color secondColor, vector <CandySpeciality> specialities) {
    Color colorToHandle = firstColor != Color::MULTICOLOR ? firstColor : secondColor;

    vector <vector<int>> cellsToCrush = {{firstCellPosition.x,  firstCellPosition.y},
                                         {secondCellPosition.x, secondCellPosition.y}};

    sendScoreMulticolor(specialities.at(0));
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToHandle) {
                setCellAt(specialities.at(rand() % specialities.size()), colorToHandle, i, j);
                //Choose randomly between specialities sent, this is done because of the striped case
                cellsToCrush.push_back({i, j});
            }
        }
        handleCellsToReplace(cellsToCrush);
    }
}

void MatchHandler::normalCandyAndMulticolorInteraction(Color colorToRemove, Point multicolorPosition) {
    sendInteractionScore(NONE_MULTICOLOR);
    moveCellsDown(vector < vector < int >> ({{ multicolorPosition.x, multicolorPosition.y }}));
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToRemove) {
                handleCellsToReplace(vector < vector < int >> ({{ i, j }}));
            }
        }
    }
}

void
MatchHandler::doubleStripedOrWrappedInteraction(Point firstCellPosition, Point secondCellPosition, int leftOffset,
                                                int rightOffset) {
    if (leftOffset == -1) 
        sendInteractionScore(STRIPED_WRAPPED);
    else sendInteractionScore(DOUBLE_STRIPED);
    
    for (int offset = leftOffset; offset <= rightOffset; offset++) {
        vector <vector<int>> cellsToMove;
        handleStrippedHorizontal(firstCellPosition.x + offset, firstCellPosition.y, cellsToMove);
    }
    for (int offset = leftOffset; offset <= rightOffset; offset++) {
        vector <vector<int>> cellsToMove;
        handleStrippedVertical(firstCellPosition.x, firstCellPosition.y + offset, cellsToMove);
    }
}


void MatchHandler::doubleWrappedInteraction(Point firstCellPosition, Point secondCellPosition) {
    sendInteractionScore(DOUBLE_WRAPPED);
    vector <vector<int>> cellsToMove;
    handleWrapped(firstCellPosition.x, firstCellPosition.y, cellsToMove, -2, 2);
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