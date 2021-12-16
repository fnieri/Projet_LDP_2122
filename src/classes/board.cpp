
#include "board.h"

#include <utility>

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), margin(margin),
                                                            numberOfCells(numberOfCells) {
    matchDetector = make_unique<MatchDetection>(this);
    eventHandler = make_unique<EventHandler>(this);

    int y = margin;
    int size = sqrt(numberOfCells);
    for (int i = 0; i < size; ++i) {
        vector<Cell> cellRow;
        for (int j = 0; j < size; ++j) {
            Point center{margin * j + margin, y};
            Candy candy = CandyFactory::generateCandy(CandySpeciality::NONE);
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
            cell.setCandy(CandyFactory::generateCandy(CandySpeciality::NONE));
        }
    }
    while (checkMatches()) {}

    CellsVertex[5][6].setCandy(CandyFactory::generateCandy(STRIPED_HORIZONTAL));
    // CellsVertex[5][5].setCandy(CandyFactory::generateCandy(MULTICOLOR));
    while (matchDetector->checkMatches()) {}
    setAcceptInput(true);
};


void Board::draw() {
    for (auto &cellRow: CellsVertex) {
        for (auto &cell: cellRow) {
            cell.draw();
        }
    }
}

bool Board::contains(Point p) {
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


void Board::handleMouseEvent(Point p) {
    eventHandler->handleMouseEvent(p);
}


bool Board::isInputAllowed() {
    return acceptInput;
}

Cell *Board::cellAt(Point p) {
    for (auto & i : CellsVertex) {
        for (auto & j : i) {
            if (j.contains(p)) {
                return &j;
            }
        }
    }
    return nullptr;
}

vector<vector<Cell>> Board::getCells() {
    return this->CellsVertex;
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

void Board::setAcceptInput(bool newState) {
    acceptInput = newState;
}

void Board::setCellAt(CandySpeciality newSpeciality, Color newColor, int i, int j) {
    CellsVertex[i][j].setCandy(CandyFactory::generateCandy(newSpeciality, newColor));
}

void Board::createSpecialCandy(int i, int j, CandySpeciality speciality) {
    if (speciality == CandySpeciality::MULTICOLOR)
        CellsVertex[i][j].setCandy(
                CandyFactory::generateCandy(speciality));
    else
        CellsVertex[i][j].setCandy(
                CandyFactory::generateCandy(speciality, CellsVertex[i][j].getColor()));
}

void Board::highlight(Point p) {
    for (auto &i: CellsVertex) {
        for (auto &j: i) {
            if (j.contains(p)) j.setHighlighted(true);
            else j.setHighlighted(false);
        }
    }
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

bool Board::checkMatches() {
    return matchDetector->checkMatches();
}

void Board::moveCells(vector<vector<int>> cellsToReplace) {
    Animation::moveCellsDown(this, std::move(cellsToReplace), &CellsVertex, margin);
}

void Board::swapCellsNoAnim(Cell *cell1, Cell *cell2) {
    Candy firstCellCandy = cell1->getCandy();
    cell1->setCandy(cell2->getCandy());
    cell2->setCandy(firstCellCandy);

}

void Board::exchangeCells(Cell *cell1, Cell *cell2) {
    if (!matchDetector->checkForCandiesInteraction(cell1, selectedCellPosition, cell2, toSwapCellPosition)) {
        cell1->animateCandy(cell2);

        Candy selectedCellCandy = cell1->getCandy();
        Point selectedCellCenter = cell1->getCenter();

        cell1->setCandy(cell2->getCandy());
        cell2->setCandy(selectedCellCandy);

        cell1->setCenter(cell2->getCenter());
        cell2->setCenter(selectedCellCenter);
    }
}

bool Board::isMoveAllowed(Point cell1Position, Point cell2Position) {
    if ((cell1Position.x == cell2Position.x && std::abs(cell1Position.y - cell2Position.y) == 1) ||
        (cell1Position.y == cell2Position.y && std::abs(cell1Position.x - cell2Position.x) == 1))
        return true;
    return false;
}

void Board::swapCells(Cell *swapCell, Point swapCellPosition) {
    setAcceptInput(false);
    if (isMoveAllowed(selectedCellPosition, swapCellPosition)) {
        exchangeCells(selectedCell, swapCell);
        if (!checkMatches()) {
            exchangeCells(selectedCell, swapCell);
        } else while (checkMatches()) {}
    }
    selectedCell = nullptr;
    setAcceptInput(true);
}
