#include "board.h"

#include <utility>

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), margin(margin),
                                                            numberOfCells(numberOfCells) {
    matchDetector = make_unique<MatchDetection>(this);
    int y = margin;
    int size = sqrt(numberOfCells);
    for (int i = 0; i < size; ++i) {
        vector<Cell> cellRow;
        for (int j = 0; j < size; ++j) {
            Point center{margin * j + margin, y};
            Candy candy = CandyFactory::generateCandy(CandySpeciality::NONE);
            Cell cell{center, cellSize, candy};
            cellRow.push_back(cell);
        }
        CellsVertex.push_back(cellRow);
        y += margin;
    };
}

vector<vector<Cell>> Board::getCells() {
    return this->CellsVertex;
}

void Board::reset() {
    for (auto &row: CellsVertex) {
        for (auto &cell: row) {
            cell.setCandy(CandyFactory::generateCandy(CandySpeciality::NONE));
        }
    }
    while (checkMatches()) {}
    CellsVertex[5][2].setCandy(CandyFactory::generateCandy(CandySpeciality::STRIPED_HORIZONTAL, Color::BLUE));
    CellsVertex[4][3].setCandy(CandyFactory::generateCandy(CandySpeciality::NONE, Color::BLUE));
    CellsVertex[6][2].setCandy(CandyFactory::generateCandy(CandySpeciality::NONE, Color::BLUE));
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

void Board::createSpecialCandy(int i, int j, CandySpeciality speciality) {
    if (speciality == CandySpeciality::MULTICOLOR)
        CellsVertex[i][j].setCandy(
                CandyFactory::generateCandy(speciality));
    else
        CellsVertex[i][j].setCandy(
                CandyFactory::generateCandy(speciality, CellsVertex[i][j].getColor()));
}

bool Board::checkMatches() {
    return matchDetector->checkMatches();
}

void Board::moveCells(vector<vector<int>> cellsToReplace) {
    Animation::moveCellsDown(this, std::move(cellsToReplace), &CellsVertex, margin);
}

void Board::exchangeCells(Cell *cell1, Cell *cell2) {
    cell1->animateCandy(cell2);

    Candy selectedCellCandy = cell1->getCandy();
    Point selectedCellCenter = cell1->getCenter();

    cell1->setCandy(cell2->getCandy());
    cell2->setCandy(selectedCellCandy);

    cell1->setCenter(cell2->getCenter());
    cell2->setCenter(selectedCellCenter);
}

bool Board::isMoveAllowed(Point cell1Position, Point cell2Position) {
    if ((cell1Position.x == cell2Position.x && std::abs(cell1Position.y - cell2Position.y) == 1) ||
        (cell1Position.y == cell2Position.y && std::abs(cell1Position.x - cell2Position.x) == 1))
        return true;
    return false;
}

void Board::swapCells(Cell *swapCell, Point swapCellPosition) {
    if (isMoveAllowed(selectedCellPosition, swapCellPosition)) {
        exchangeCells(selectedCell, swapCell);
        if (!checkMatches()) {
            exchangeCells(selectedCell, swapCell);
        } else while (checkMatches()) {}
    }
    selectedCell = nullptr;
}
