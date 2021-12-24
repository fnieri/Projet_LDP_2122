//
// Created by louis on 19/12/2021.
//

#include "MatchHandler.h"

void MatchHandler::handleCellsToReplace(vector <vector<int>> cellsToReplace) {
    vector <vector<int>> specialCells;
    for (auto &cell: cellsToReplace) {
        CandySpeciality speciality = CellsVertex[cell[0]][cell[1]].getSpeciality();
        if (speciality != NONE) {
            specialCells.push_back(cell);
        } else {
            emptyCell(cell[0], cell[1]);
        }
    }
//    emptyCells(cellsToReplace);
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
    handleCellsToReplace(cellsToMove);

}

void MatchHandler::emptyCell(int i, int j) {
    CellsVertex[i][j].setCandy(generateEmptyCandy());
}

void MatchHandler::emptyCells(vector <vector<int>> cellsToEmpty) {
    for (auto &cellToEmpty: cellsToEmpty)
        emptyCell(cellToEmpty[0], cellToEmpty[1]);
}


void MatchHandler::MultiColorInteractions(Point firstCellPosition, Point secondCellPosition, Color firstColor,
                                          Color secondColor, vector <CandySpeciality> specialities) {
    Color colorToHandle = firstColor != Color::MULTICOLOR ? firstColor : secondColor;
    //Firstly remove multicolor and other candy because they wont be removed after
//    moveCellsDown(vector < vector < int >> ({
//        { firstCellPosition.x, firstCellPosition.y },
//        { secondCellPosition.x, secondCellPosition.y }
//    }));

    vector <vector<int>> cellsToCrush = {{firstCellPosition.x,  firstCellPosition.y},
                                         {secondCellPosition.x, secondCellPosition.y}};
//    if (firstColor == Color::MULTICOLOR) cellsToCrush.push_back({firstCellPosition.x, firstCellPosition.y});
//    else cellsToCrush.push_back({secondCellPosition.x, secondCellPosition.y});

    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToHandle) {
                setCellAt(static_cast<CandySpeciality>(rand() % specialities.size()), colorToHandle, i, j);
                //Choose randomly between specialities sent, this is done because of the striped case
                // that makes no fucking sense my guy
                cellsToCrush.push_back({i, j});
            }
        }
    }
    handleCellsToReplace(cellsToCrush);
}

void MatchHandler::normalCandyAndMulticolorInteraction(Color colorToRemove, Point multicolorPosition) {
    moveCellsDown(vector < vector < int >> ({{ multicolorPosition.x, multicolorPosition.y }}));
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToRemove) {
                handleCellsToReplace(vector < vector < int >> ({{ i, j }}));
//                moveCellsDown(vector < vector < int >> ({{ i, j }}));
            }
        }
    }
}

void
MatchHandler::doubleStripedOrWrappedInteraction(Point firstCellPosition, Point secondCellPosition, int leftOffset,
                                                int rightOffset) {
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
    vector <vector<int>> cellsToMove;
    handleWrapped(firstCellPosition.x, firstCellPosition.y, cellsToMove, -2, 2);
}

void
MatchHandler::stripedMulticolorInteraction(Point firstCellPosition, Point secondCellPosition, Color colorToStripe) {
    moveCellsDown(vector < vector < int >> {{firstCellPosition.x,  firstCellPosition.y},
                                            {secondCellPosition.x, secondCellPosition.y}});
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        vector <vector<int>> cellsToCrush;
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToStripe) {
                //Choose randomly between striped horizontal and vertical
                setCellAt(static_cast<CandySpeciality>(rand() % 2 + 1), colorToStripe, i, j);
                //Choose randomly between striped orientation
                cellsToCrush.push_back({i, j});
            }
        }
        Fl::wait(0.3);
        moveCellsDown(cellsToCrush);

    }
}


void
MatchHandler::wrappedAndMulticolorInteraction(Point firstCellPosition, Point secondCellPosition, Color colorToWrap) {
    emptyCells(vector < vector < int >> {{firstCellPosition.x,  firstCellPosition.y},
                                         {secondCellPosition.x, secondCellPosition.y}});
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        vector <vector<int>> cellsToCrush;
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToWrap) {
                CellsVertex[i][j].setCandy(generateCandy(BOMB, colorToWrap));
                cellsToCrush.push_back({i, j});
            }
            moveCellsDown(cellsToCrush);
        }
    }
}

void MatchHandler::doubleMulticolorInteraction() {
    reset();
}