#include "board.h"

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), margin(margin),
                                                            numberOfCells(numberOfCells) {
    matchDetector = make_unique<MatchDetection>(this);
    int y = 60;
    int size = sqrt(numberOfCells);
    for (int i = 0; i < size; ++i) {
        vector<Cell> cellRow;
        for (int j = 0; j < size - 1; ++j) {
            
            Point center{margin * j + margin, y};
                Candy candy = CandyFactory::generateCandy(CandySpeciality::MULTICOLOR);
                Cell cell{center, cellSize, candy};
                cellRow.push_back(cell);
        }
        CellsVertex.push_back(cellRow);
        y += margin;
    };
  
}

vector<vector<Cell>> Board::getCells(){
        return this->CellsVertex;
}

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
                    selectedCellPosition = Point{i, j};
                } else swapCells(&CellsVertex[i][j], Point{i, j});
                return true;
            }
        }
    }
    return false;
}

void Board::checkMatches() {
    matchDetector->checkMatches();
}


void Board::createSpecialCandy(int i, int j, CandySpeciality speciality) {
    if (speciality == CandySpeciality::MULTICOLOR)
        CellsVertex[i][j].setCandy(
                CandyFactory::generateCandy(speciality));
    else
        CellsVertex[i][j].setCandy(
                CandyFactory::generateCandy(speciality, CellsVertex[i][j].getColor()));
}


void Board::moveCells(vector<vector<int>> cellsToReplace) {
    for (auto &cellToReplace: cellsToReplace) {
        int i = cellToReplace[0];
        int j = cellToReplace[1];
        // drops all candy one cell under then generates candy for top cell
        for (int k = i; k > 0; k--) {
            CellsVertex[k][j].setCandy(CellsVertex[k - 1][j].getCandy());
        }
        CellsVertex[0][j].setCandy(CandyFactory::generateCandy(CandySpeciality::NONE));
    }
}


void Board::exchangeCells(Cell *cell1, Cell *cell2) {
    if (!matchDetector->checkForCandiesInteraction(cell1->getCandy(), cell2->getCandy())) {
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
    if (isMoveAllowed(selectedCellPosition, swapCellPosition)) {
        exchangeCells(selectedCell, swapCell);
        if (!matchDetector->checkMatches()) {
            exchangeCells(selectedCell, swapCell);
        } else {
            while (matchDetector->checkMatches()) {}
        }
    }
    selectedCell = nullptr;
}

