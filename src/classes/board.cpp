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
    int x = 0;
    int y = 0;
    for (auto &cellRow: CellsVertex) {
        ++x;
        for (auto &cell: cellRow) {
            ++y;
            if (cell.contains(p)) {
                std::cout << x << " " << y << std::endl;
                return true;
            }
        }
    }
    return false;
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
            if (checkHorizontalMatch(i, j)) continue;
            if (checkVerticalMatch(i, j)) continue;
        }
    }
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

//    for (int i = 0; i < CellsVertex.size(); i++) {
//        for (int j = 0; j < CellsVertex[i].size(); j++) {
//
//            if (CellsVertex[i][j].getColor() == Color::GREEN) {
//                continue;
//            }
//        }
//    }



/*
vector<Cell> Board::getCells(){
    return this->CellsVertex;
}
*/
// void Board::handleClick(Point mouseLoc) {
// //    // determine which cell was clicked
//     for (auto &cell: CellsVertex) {
//         cout << cell.contains(mouseLoc);
//     }
// }
//
//}