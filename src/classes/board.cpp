#include "board.h"

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), margin(margin),
                                                            numberOfCells(numberOfCells) {
    int y = 60;
    int size = sqrt(numberOfCells);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Point center{margin + j * margin, y};
            // add to vector
            Cell cell{center, cellSize, FL_GREEN};
            CellsVertex.push_back(cell);
        }
        y += margin;
    };
}

void Board::draw() {
    for (auto &cell: CellsVertex) {
        cell.draw();
    }
}

bool Board::contains(Point p) {
    for (auto &cell: CellsVertex) {
        if (cell.contains(p)) {
            cell.setColor(FL_RED);
            return true;
        }
    }
    return false;
}

//void Board::handleClick() {
//    // determine which cell was clicked
//
//
//}