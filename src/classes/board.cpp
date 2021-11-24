#include "board.h"

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), margin(margin),
                                                            numberOfCells(numberOfCells) {
    CandyFactory* candyFactory = new CandyFactory();
    int y = 60;
    int size = sqrt(numberOfCells);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Point center{ margin * j + margin, y};
            Candy candy = candyFactory->generateCandy(center, CandySpeciality::NONE);
            // add to vector
            Cell cell{center, cellSize, FL_GREEN, candy};
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
            cout << "true";
            return true;
        }
    }
    return false;
}
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