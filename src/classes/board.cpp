//
// Created by louis on 19/12/2021.
//

#include "Board.h"

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), margin(margin),
                                                            numberOfCells(numberOfCells) {
    int y = margin;
    int size = sqrt(numberOfCells);
    for (int i = 0; i < size; ++i) {
        vector <Cell> cellRow;
        for (int j = 0; j < size; ++j) {
            Point center{margin * j + margin, y};
            Candy candy = generateCandy(CandySpeciality::NONE);
            Cell cell{center, cellSize, candy, margin};
            cellRow.push_back(cell);
        }
        CellsVertex.push_back(cellRow);
        y += margin;
    }
}

void Board::reset() {
    setAcceptInput(false);

    for (auto &row: CellsVertex) {
        for (auto &cell: row) {
            cell.setCandy(generateCandy(CandySpeciality::NONE));
        }
    }
    while (checkMatches()) {}

    CellsVertex[5][6].setCandy(generateCandy(STRIPED_HORIZONTAL));
    // CellsVertex[5][5].setCandy(CandyFactory::generateCandy(MULTICOLOR));
    while (checkMatches()) {}
    setAcceptInput(true);
};

void Board::draw() {
    for (auto &cellRow: CellsVertex) {
        for (auto &cell: cellRow) {
            cell.draw();
        }
    }
}

bool Board::handleBoardContains(Point p) {
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
    for (auto &i: CellsVertex) {
        for (auto &j: i) {
            if (j.contains(p)) {
                return &j;
            }
        }
    }
    return nullptr;
}

Point Board::getPositionOfCell(Point p) {
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
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
    selectedCellPosition = getPositionOfCell(p);
}

void Board::setSwapCell(Cell *newCell) {
    toSwapCell = newCell;
}

void Board::setSwapCellPosition(Point p) {
    toSwapCellCenter = getPositionOfCell(p);
}

void Board::setCellAt(CandySpeciality newSpeciality, Color newColor, int i, int j) {
    CellsVertex[i][j].setCandy(generateCandy(newSpeciality, newColor));
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
    while (checkMatches()) {}
}

void Board::swapCells(Cell *swapCell, Point swapCellPosition) {
    setAcceptInput(false);
    unHighlightAll();
    if (isMoveAllowed(selectedCellPosition, swapCellPosition)) {
        exchangeCells(selectedCell, swapCell);
        if (!checkMatches()) {
            exchangeCells(selectedCell, swapCell);
        } else {
            while (checkMatches()) {};
//            checkIfShuffleIsNeeded();
        }
    }
    selectedCell = nullptr;
    setAcceptInput(true);
}

void Board::swapCellsNoAnim(Cell *cell1, Cell *cell2) {
    Candy firstCellCandy = cell1->getCandy();
    cell1->setCandy(cell2->getCandy());
    cell2->setCandy(firstCellCandy);
}

void Board::exchangeCells(Cell *cell1, Cell *cell2) {
    if (!checkForCandiesInteraction(cell1, selectedCellPosition, cell2, toSwapCellPosition)) {
        cell1->animateCandy(cell2);
        Candy _selectedCellCandy = cell1->getCandy();
        Point _selectedCellCenter = cell1->getCenter();

        cell1->setCandy(cell2->getCandy());
        cell2->setCandy(_selectedCellCandy);

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