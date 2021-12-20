//
// Created by louis on 19/12/2021.
//

#include "MatchHandler.h"


void MatchHandler::handleStrippedHorizontal(vector <vector<Cell>> *CellVector, int i, int j,
                                            vector <vector<int>> cellsToMove) {
    for (int k = 0; k < (int) (*CellVector)[i].size(); ++k) {
        vector<int> cellToMove = {i, k};
        if (find(cellsToMove.begin(), cellsToMove.end(), cellToMove) == cellsToMove.end()) {
            cellsToMove.push_back(cellToMove);
        }
    }
    emptyCells(cellsToMove, CellVector);
    board->moveCells(cellsToMove);
}

void MatchHandler::handleStrippedVertical(vector <vector<Cell>> *CellVector, int i, int j,
                                          vector <vector<int>> cellsToMove) {
    for (int k = 0; k < (int) (*CellVector)[i].size(); ++k) {
        vector<int> cellToMove = {k, j};
        if (find(cellsToMove.begin(), cellsToMove.end(), cellToMove) == cellsToMove.end()) {
            cellsToMove.push_back(cellToMove);
        }
    }
    emptyCells(cellsToMove, CellVector);
    board->moveCells(cellsToMove);
}

void MatchHandler::handleWrapped(vector <vector<Cell>> *CellVector, int i, int j,
                                 vector <vector<int>> cellsToMove, int leftDownMargin, int rightUpMargin) {
    for (int k = leftDownMargin; k <= rightUpMargin; ++k) {
        for (int l = leftDownMargin; l <= rightUpMargin; ++l) {
            vector<int> cellToMove = {i + k, j + l};
            if ((i + k >= 0 && i + k < (*CellVector)[i].size()) && (j + l >= 0 && j + l < (*CellVector)[j].size())) {
                cellsToMove.push_back(cellToMove);
            }
        }
    }
    emptyCells(cellsToMove, CellVector);
    board->moveCells(cellsToMove);
}

void MatchHandler::emptyCell(vector <vector<Cell>> *CellVector, int i, int j) {
    (*CellVector)[i][j].setCandy(CandyFactory::generateEmptyCandy());
}

void MatchHandler::emptyCells(vector <vector<int>> cellsToEmpty, vector <vector<Cell>> *CellVector) {
    for (auto &cellToEmpty: cellsToEmpty)
        emptyCell(CellVector, cellToEmpty[0], cellToEmpty[1]);
}


void MatchHandler::MultiColorInteractions(Point firstCellPosition, Point secondCellPosition, Color firstColor,
                                          Color secondColor, vector <CandySpeciality> specialities) {
    Color colorToHandle = firstColor != Color::MULTICOLOR ? firstColor : secondColor;
    //Firstly remove multicolor and other candy because they wont be removed after
    moveCells(vector < vector < int >> ({
        { firstCellPosition.x, firstCellPosition.y },
        { secondCellPosition.x, secondCellPosition.y }
    }));

    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        vector <vector<int>> cellsToCrush;
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToHandle) {

                setCellAt(static_cast<CandySpeciality>(rand() % specialities.size()), colorToHandle, i, j);
                //Choose randomly between specialities sent, this is done because of the striped case
                cellsToCrush.push_back({i, j});

            }
        }
        moveCells(cellsToCrush);
    }
}

void MatchHandler::normalCandyAndMulticolorInteraction(Color colorToRemove, Point multicolorPosition) {
    moveCells(vector < vector < int >> ({{ multicolorPosition.x, multicolorPosition.y }}));
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToRemove) {
                moveCells(vector < vector < int >> ({{ i, j }}));
            }
        }
    }
}

void
MatchHandler::doubleStripedOrWrappedInteraction(Point firstCellPosition, Point secondCellPosition, int leftOffset,
                                                int rightOffset) {
    for (int offset = leftOffset; offset <= rightOffset; offset++) {
        vector <vector<int>> cellsToMove;
        handleStrippedHorizontal(candyBoard.get(), &CellsVertex, firstCellPosition.x + offset,
                                 firstCellPosition.y, cellsToMove);
    }
    for (int offset = leftOffset; offset <= rightOffset; offset++) {
        vector <vector<int>> cellsToMove;
        handleStrippedVertical(candyBoard.get(), &CellsVertex, firstCellPosition.x,
                               firstCellPosition.y + offset, cellsToMove);
    }
}


void MatchHandler::doubleWrappedInteraction(Point firstCellPosition, Point secondCellPosition) {
    vector <vector<int>> cellsToMove;
    handleWrapped(candyBoard.get(), &CellsVertex, firstCellPosition.x, firstCellPosition.y, cellsToMove, -2,
                  2);
}

void
MatchHandler::stripedMulticolorInteraction(Point firstCellPosition, Point secondCellPosition, Color colorToStripe) {
    moveCells(vector < vector < int >> {{firstCellPosition.x,  firstCellPosition.y},
                                        {secondCellPosition.x, secondCellPosition.y}});
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        vector <vector<int>> cellsToCrush;
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToStripe) {
                setCellAt(static_cast<CandySpeciality>(rand() % 2 + 1), colorToStripe, i,
                          j);      //Choose randomly between striped horizontal and vertical
                //Choose randomly between striped orientation
                cellsToCrush.push_back({i, j});
            }
        }
        Fl::wait(0.3);
        moveCells(cellsToCrush);

    }
}


void
MatchHandler::wrappedAndMulticolorInteraction(Point firstCellPosition, Point secondCellPosition, Color colorToWrap) {
    Animation::emptyCells(vector < vector < int >> {{firstCellPosition.x,  firstCellPosition.y},
                                                    {secondCellPosition.x, secondCellPosition.y}}, &CellsVertex);
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        vector <vector<int>> cellsToCrush;
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToWrap) {
                CellsVertex[i][j].setCandy(CandyFactory::generateCandy(BOMB, colorToWrap));
                cellsToCrush.push_back({i, j});
            }
            moveCells(cellsToCrush);
        }
    }
}

void MatchHandler::doubleMulticolorInteraction() {
    reset();
}