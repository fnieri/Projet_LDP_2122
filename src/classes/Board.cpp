//
// Created by louis on 19/12/2021.
//

#include "Board.h"

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), numberOfCells(numberOfCells) {
    setMargin(margin);
    CellsVertex = LevelFactory::buildCellVector("levels/level_1.txt", margin, cellSize, numberOfCells);
    getInitialHighScore();  
}

void Board::reset() {  
    for (auto &row: CellsVertex) {
        for (auto &cell: row) {
            cell.setObject(ClickableFactory::generateCandy(CandySpeciality::NONE));
        }
    }
    while (checkMatches());
    CellsVertex[5][5].setObject(ClickableFactory::makeCandy(MULTICOLOR));
    CellsVertex[5][6].setObject(ClickableFactory::makeCandy(MULTICOLOR));
};

void Board::draw() {
    for (auto &cellRow: CellsVertex) {
        for (auto &cell: cellRow) {
            cell.draw();
        }
    }
}

void Board::handleBoardDrag(Point p1, Point p2) {
    setAcceptInput(false);
    unHighlightAll();
    selectedCell = getCellFromPosition(p1);
    Cell *secondCell = getCellFromPosition(p2);
    if ((selectedCell && secondCell) && (isCandy(selectedCell) && isCandy(selectedCell))) {
        selectedCellCenter = selectedCell->getCenter();
        selectedCellPosition = p1;
        swapCells(secondCell, p2);
    }
    setAcceptInput(true);
}

Cell *Board::getCellFromPosition(Point p) {
    return &CellsVertex[p.x][p.y];
}

bool Board::handleBoardContains(Point p) {
    unHighlightAll();
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].contains(p)) {
                if (!selectedCell) {
                    selectedCell = &CellsVertex[i][j];
                    selectedCellCenter = selectedCell->getCenter();
                    selectedCellPosition = Point{i, j};
                } else swapCells(&CellsVertex[i][j], Point{i, j});
                return true;
            }
        }
    }
    return false;
}

Cell *Board::cellAt(Point p) {
    for (auto &row: CellsVertex) {
        for (auto &cell: row) {
            if (cell.contains(p)) return &cell;
        }
    }
    return nullptr;
}
 
Point Board::getPositionOfCell(Point p) {
    for (int i = 0; i < (int) CellsVertex.size(); ++i) {
        for (int j = 0; j < (int) CellsVertex[i].size(); ++j) {
            if (CellsVertex[i][j].contains(p)) {
                return Point{i, j};
            }
        }
    }
    return Point{};
}

void Board::setSelectedCell(Cell *newCell) {
    selectedCell = newCell;
}

void Board::setSelectedCellPosition(Point p) {
    selectedCellCenter = getPositionOfCell(p);
}

void Board::setSwapCell(Cell *newCell) {
    toSwapCell = newCell;
}

void Board::setSwapCellPosition(Point p) {
    toSwapCellPosition = getPositionOfCell(p);
}

void Board::setCellAt(CandySpeciality newSpeciality, Color newColor, int i, int j) {
    CellsVertex[i][j].setObject(ClickableFactory::makeCandy(newSpeciality, newColor));
}

void Board::shuffle() {
    for (int i = 0; i < numberOfCells; ++i) {
        int size = sqrt(numberOfCells) - 1;
        int x1 = rand() % size;
        int y1 = rand() % size;
        int x2 = rand() % size;
        int y2 = rand() % size;
        swapCellsNoAnim(&CellsVertex[x1][y1], &CellsVertex[x2][y2]);
    }
    while (checkMatches());
}

void Board::swapCells(Cell *swapCell, Point swapCellPosition) {
    setAcceptInput(false);
    if (isMoveAllowed(selectedCellPosition, swapCellPosition)) {
        if (isCandy(selectedCell) && isCandy(swapCell)) {
            exchangeCells(selectedCell, swapCell);
            if (checkForCandiesInteraction(selectedCell, selectedCellPosition, swapCell, toSwapCellPosition)) {
                selectedCell = nullptr;
                while (checkMatches());
                while (!checkIfShuffleIsNeeded()) shuffle();
                return;
            }
            if (!checkMatches()) {
                exchangeCells(selectedCell, swapCell);
            } else {
                while (checkMatches());
                while (!checkIfShuffleIsNeeded()) shuffle();
            }
            decreaseMovesLeft();
        }
    }
    selectedCell = nullptr;
    setAcceptInput(true);
}

bool Board::checkIfShuffleIsNeeded() {
    vector <array<int, 2>> deltas = {{0,  1},
                                     {1,  0},
                                     {0,  -1},
                                     {-1, 0}};
    for (int i = 0; i < (int) CellsVertex.size(); ++i) {
        for (int j = 0; j < (int) CellsVertex[i].size(); ++j) {
            Cell *tempCell = &CellsVertex[i][j];
            for (auto d: deltas) {
                try {
                    int dx = d[0];
                    int dy = d[1];
                    Cell *tempSwapCell = &CellsVertex.at(i + dy).at(j + dx);
                    swapCellsNoAnim(tempCell, tempSwapCell);
                    setHandleMatch(false);
                    if (checkMatches()) {
                        swapCellsNoAnim(tempCell, tempSwapCell);
                        setHandleMatch(true);
                        return true;
                    }
                    swapCellsNoAnim(tempCell, tempSwapCell);
                }
                catch (out_of_range &e) {
                    continue;
                }
            }
        }
    }
    setHandleMatch(true);
    return false;
}

void Board::swapCellsNoAnim(Cell *cell1, Cell *cell2) {
    if (isCandy(cell1) && isCandy(cell2)) {
        Candy firstCellCandy = *cell1->getCandy();
        cell1->setObject(*cell2->getCandy());
        cell2->setObject(firstCellCandy);
    }
}

void Board::exchangeCells(Cell *cell1, Cell *cell2) {
    if (isCandy(cell1) && isCandy(cell2)) {
        cell1->animateCandy(cell2);
        Candy _selectedCellCandy = *cell1->getCandy();
        Point _selectedCellCenter = cell1->getCenter();

        cell1->setObject(*cell2->getCandy());
        cell2->setObject(_selectedCellCandy);

        cell1->setCenter(cell2->getCenter());
        cell2->setCenter(_selectedCellCenter);
    }
}

bool Board::isMoveAllowed(Point cell1Position, Point cell2Position) {
    if ((cell1Position.x == cell2Position.x && std::abs(cell1Position.y - cell2Position.y) == 1) ||
        (cell1Position.y == cell2Position.y && std::abs(cell1Position.x - cell2Position.x) == 1))
        return true;
    return false;
}