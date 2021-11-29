#include "board.h"

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), margin(margin),
                                                            numberOfCells(numberOfCells) {

    int y = 60;
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

bool Board::checkMatchFive(int i, int j) {
    // find cookie
    try {
        if (CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 2).getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 1).getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 1).getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 2).getColor()) {
            vector<vector<int>> cellsToRemove{{i, j - 2},
                                              {i, j - 1},
                                              {i, j + 1},
                                              {i, j + 2}};
            createSpecialCandy(i, j, CandySpeciality::MULTICOLOR);
            moveCells(cellsToRemove);
            return true;
        } else if (CellsVertex[i][j].getColor() == CellsVertex.at(i - 2)[j].getColor() &&
                   CellsVertex[i][j].getColor() == CellsVertex.at(i - 1)[j].getColor() &&
                   CellsVertex[i][j].getColor() == CellsVertex.at(i + 1)[j].getColor() &&
                   CellsVertex[i][j].getColor() == CellsVertex.at(i + 2)[j].getColor()) {
            vector<vector<int>> cellsToRemove{{i - 2, j},
                                              {i - 1, j},
                                              {i + 1, j},
                                              {i + 2, j}};
            createSpecialCandy(i, j, CandySpeciality::MULTICOLOR);
            moveCells(cellsToRemove);
            return true;
        }
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}

bool Board::checkWrappedCandy(int i, int j) {
    try {
        // check for + shape
        if (CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 1).getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 1).getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex.at(i - 1)[j].getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex.at(i + 1)[j].getColor()) {
            vector<vector<int>> cellsToRemove{{i,     j - 1},
                                              {i,     j + 1},
                                              {i - 1, j},
                                              {i + 1, j}};
            createSpecialCandy(i, j, CandySpeciality::BOMB);
            moveCells(cellsToRemove);
            return true;

        }
            // check for T shape
        else if (CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 1).getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 1).getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex.at(i - 1)[j].getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex.at(i - 2)[j].getColor()) {
            vector<vector<int>> cellsToRemove{{i,     j - 1},
                                              {i,     j + 1},
                                              {i - 1, j},
                                              {i - 2, j}};
            createSpecialCandy(i, j, CandySpeciality::BOMB);
            moveCells(cellsToRemove);
            return true;
        }
            // check for inverse T shape
        else if (CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 1).getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 1).getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex.at(i + 1)[j].getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex.at(i + 2)[j].getColor()) {
            vector<vector<int>> cellsToRemove{{i,     j - 1},
                                              {i,     j + 1},
                                              {i + 1, j},
                                              {i + 2, j}};
            createSpecialCandy(i, j, CandySpeciality::BOMB);
            moveCells(cellsToRemove);
            return true;
        }
            // check for sideways left T shape
        else if (CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 1).getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 2).getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex.at(i - 1)[j].getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex.at(i + 1)[j].getColor()) {
            vector<vector<int>> cellsToRemove{{i,     j + 1},
                                              {i,     j + 2},
                                              {i - 1, j},
                                              {i + 1, j}};
            createSpecialCandy(i, j, CandySpeciality::BOMB);
            moveCells(cellsToRemove);
            return true;
        }
            // check for L shape
        else if (CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 1).getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 2).getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex.at(i + 1)[j].getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex.at(i + 2)[j].getColor()) {
            vector<vector<int>> cellsToRemove{{i,     j + 1},
                                              {i,     j + 2},
                                              {i + 1, j},
                                              {i + 2, j}};
            createSpecialCandy(i, j, CandySpeciality::BOMB);
            moveCells(cellsToRemove);
            return true;
        }
            // check for inverse L shape
        else if (CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 1).getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 2).getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex.at(i - 1)[j].getColor() &&
                 CellsVertex[i][j].getColor() == CellsVertex.at(i - 2)[j].getColor()) {
            vector<vector<int>> cellsToRemove{{i,     j - 1},
                                              {i,     j - 2},
                                              {i - 1, j},
                                              {i - 2, j}};
            createSpecialCandy(i, j, CandySpeciality::BOMB);
            moveCells(cellsToRemove);
            return true;
        }
        // this is annoying asf imma have to find a more efficient way to do this
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }

}

bool Board::checkHorizontalMatchFour(int i, int j) {
    try {
        if (CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 2).getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 1).getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 1).getColor()) {
            vector<vector<int>> cellsToRemove{{i, j - 2},
                                              {i, j - 1},
                                              {i, j + 1}};
            createSpecialCandy(i, j, CandySpeciality::STRIPED_HORIZONTAL);
            moveCells(cellsToRemove);
            return true;
        } else if (CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 1).getColor() &&
                   CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 1).getColor() &&
                   CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 2).getColor()) {
            vector<vector<int>> cellsToRemove{{i, j - 1},
                                              {i, j + 1},
                                              {i, j + 2}};
            createSpecialCandy(i, j, CandySpeciality::STRIPED_HORIZONTAL);
            moveCells(cellsToRemove);
            return true;
        }
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}

bool Board::checkVerticalMatchFour(int i, int j) {
    try {
        if (CellsVertex[i][j].getColor() == CellsVertex.at(i - 2)[j].getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex.at(i - 1)[j].getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex.at(i + 1)[j].getColor()) {
            vector<vector<int>> cellsToRemove{{i - 2, j},
                                              {i - 1, j},
                                              {i + 1, j}};
            createSpecialCandy(i, j, CandySpeciality::STRIPED_VERTICAL);
            moveCells(cellsToRemove);
            return true;
        } else if (CellsVertex[i][j].getColor() == CellsVertex.at(i - 1)[j].getColor() &&
                   CellsVertex[i][j].getColor() == CellsVertex.at(i + 1)[j].getColor() &&
                   CellsVertex[i][j].getColor() == CellsVertex.at(i + 2)[j].getColor()) {
            vector<vector<int>> cellsToRemove{{i - 1, j},
                                              {i + 1, j},
                                              {i + 2, j}};
            createSpecialCandy(i, j, CandySpeciality::STRIPED_VERTICAL);
            moveCells(cellsToRemove);
            return true;
        }
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}

bool Board::checkHorizontalMatch(int i, int j) {
    try {
        if (CellsVertex[i].at(j - 1).getColor() == CellsVertex[i][j].getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 1).getColor()) {
            vector<vector<int>> cellsToRemove{{i, j - 1},
                                              {i, j},
                                              {i, j + 1}}; // order doesn't matter
            moveCells(cellsToRemove);
            return true;
        }
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}

bool Board::checkVerticalMatch(int i, int j) {
    try {
        if (CellsVertex.at(i - 1)[j].getColor() == CellsVertex[i][j].getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex.at(i + 1)[j].getColor()) {
            vector<vector<int>> cellsToRemove{{i - 1, j},
                                              {i,     j},
                                              {i + 1, j}}; // don't change order
            moveCells(cellsToRemove);
            return true;
        }
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
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
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (checkMatchFive(i, j)) return true;
            if (checkWrappedCandy(i, j)) return true;
            if (checkHorizontalMatchFour(i, j)) return true;
            if (checkVerticalMatchFour(i, j)) return true;
        }
    }
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (checkHorizontalMatch(i, j)) return true;
            if (checkVerticalMatch(i, j)) return true;
        }
    }
    return false;
}

void Board::moveCells(vector<vector<int>> cellsToReplace) {
    for (auto &cellToReplace: cellsToReplace)
        CellsVertex[cellToReplace[0]][cellToReplace[1]].setCandy(Candy{nullptr, Color::BLUE});

    for (int l = 0; l < (int) margin; ++l) {
        for (auto &cellToReplace: cellsToReplace) {
            int i = cellToReplace[0];
            int j = cellToReplace[1];
            // drops all candy one cell under then generates candy for top cell
            for (int k = i; k > 0; k--) {
                Point movingCenter{CellsVertex[k - 1][j].getCenter().x,
                                   CellsVertex[k - 1][j].getCenter().y + 1};
                CellsVertex[k - 1][j].setCenter(movingCenter);
            }
        }
        Fl::wait(0.003);
    }
    for (auto &cellToReplace: cellsToReplace) {
        int i = cellToReplace[0];
        int j = cellToReplace[1];
        for (int k = i; k > 0; k--) {
            Point originalCenter{CellsVertex[k - 1][j].getCenter().x,
                                 CellsVertex[k - 1][j].getCenter().y - margin};
            CellsVertex[k - 1][j].setCenter(originalCenter);
            CellsVertex[k][j].setCandy(CellsVertex[k - 1][j].getCandy());
        }
        CellsVertex[0][j].setCandy(CandyFactory::generateCandy(CandySpeciality::NONE));
    }
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
        } else {
            while (checkMatches()) {}
        }
    }
    selectedCell = nullptr;
}
