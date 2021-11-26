#include "board.h"

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), margin(margin),
                                                            numberOfCells(numberOfCells) {
//    CandyFactory candyFactory;
    int y = 60;
    int size = sqrt(numberOfCells);
    for (int i = 0; i < size; ++i) {
        vector<Cell> cellRow;
        for (int j = 0; j < size; ++j) {
            Point center{margin * j + margin, y};
            Candy candy = CandyFactory::generateCandy(CandySpeciality::NONE);
//            unique_ptr<Candy> candyPtr = make_unique<Candy>(candy);
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
    for (auto &cellRow: CellsVertex) {
        for (auto &cell: cellRow) {
            if (cell.contains(p)) {
                cout << "true";
                return true;
            }
        }
    }
    return false;
}

void Board::checkMatches() {
    for (int i = 0; i < CellsVertex.size(); i++) {
        std::cout << "Checking matches" << std::endl;
        for (int j = 0; j < CellsVertex[i].size(); j++) {
//            std::cout << std::to_string(static_cast<int>(CellsVertex[i][j].getColor())) << " ";

            try {
                if (CellsVertex[i].at(j - 1).getColor() == CellsVertex[i][j].getColor() &&
                    CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 1).getColor()) {
                    std::cout << "found horizontal match "
                              << std::to_string(static_cast<int>(CellsVertex[i][j].getColor()))
                              << " ";
                    vector<vector<int>> cellsToRemove{{i, j},
                                                      {i, j - 1},
                                                      {i, j + 1}};
                    moveCells(cellsToRemove);
                }
            }
            catch (const std::out_of_range &e) {
                std::cout << "Out of range" << std::endl;
            }

            try {
                if (CellsVertex.at(i - 1)[j].getColor() == CellsVertex[i][j].getColor() &&
                    CellsVertex[i][j].getColor() == CellsVertex.at(i + 1)[j].getColor()) {
                    std::cout << "found vertical match "
                              << std::to_string(static_cast<int>(CellsVertex[i][j].getColor()))
                              << " ";
                    vector<vector<int>> cellsToRemove{{i, j},
                                                      {i - 1, j},
                                                      {i + 1, j}};
                    moveCells(cellsToRemove);
                }
            }
            catch (const std::out_of_range &e) {
                std::cout << "Out of range" << std::endl;
            }

        }
        std::cout << std::endl;
    }
}

void Board::moveCells(vector<vector<int>> cellsToReplace) {
    std::cout << "moving cells" << std::endl;
    for (auto &cellToReplace: cellsToReplace) {
        int i = cellToReplace[0];
        int j = cellToReplace[1];
        Candy candy = CandyFactory::generateCandy(CandySpeciality::NONE);
        CellsVertex[i][j].setCandy(candy);
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