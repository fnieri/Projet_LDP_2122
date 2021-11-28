#include "board.h"

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), margin(margin),
                                                            numberOfCells(numberOfCells) {
    matchDetector = make_unique<MatchDetection>(this);
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
    for (auto &row: CellsVertex) {
        for (auto & cell : row) {
            if (cell.contains(p)) {
//                row[j].animateCandy(&row[j - 1]);
                if (!selectedCell) selectedCell = &cell;
                else swapCells(&cell);
                return true;
            }
        }
    }
    return false;
}
/*
const int MatchDetection::matchFive[2][2][4] = 
    {
        {{0, 0, 0, 0}, {-2, -1, 1, 2}},
        {{-2, -1, 1, 2}, {0, 0, 0, 0}}
    };

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
        if (    CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 2).getColor() &&
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
            moveCells(cellsToRemove );
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
void Board::checkMatches() {
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (checkMatchFive(i, j)) continue;
            if (checkWrappedCandy(i, j)) continue;
            if (checkHorizontalMatchFour(i, j)) continue;
            if (checkVerticalMatchFour(i, j)) continue;
        }
    }
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (checkHorizontalMatch(i, j)) continue;
            if (checkVerticalMatch(i, j)) continue;
        }
    }
}

*/

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

void Board::swapCells(Cell *swapCell) {

    selectedCell->animateCandy(swapCell);

    Candy selectedCellCandy = selectedCell->getCandy();
    Point selectedCellCenter = selectedCell->getCenter();

    selectedCell->setCandy(swapCell->getCandy());
    swapCell->setCandy(selectedCellCandy);

    selectedCell->setCenter(swapCell->getCenter());
    swapCell->setCenter(selectedCellCenter);

    selectedCell = nullptr;

   matchDetector->checkMatches();
}

