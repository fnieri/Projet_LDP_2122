/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: Board.cpp
* Date: 13/01/2022
*/
        
#include "Board.h"

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), numberOfCells(numberOfCells) {
    setMargin(margin); //Margin between cells
    CellsVertex = LevelFactory::buildCellVector("levels/level_1.txt", margin, cellSize, numberOfCells);
    initializeLevel();
    getInitialHighScore();  //Set hhigh score
}


void Board::initializeLevel() {
    // replace all non candy by candy, then it checks all the matches, and finally it places back the non candy
    vector<vector<int>> nonCandyPos;
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (!isCandy(CellsVertex[i][j])) {
                int id;
                if (isIcing(CellsVertex[i][j]))
                    id = 2;
                else
                    id = 3;
                nonCandyPos.push_back({i, j, id});
                CellsVertex[i][j].setClickable(ClickableFactory::makeCandy(CandySpeciality::NONE));
            }
        }
    }
    while (checkMatches());
    for (auto &nonCandyPo: nonCandyPos) {
        int x = nonCandyPo[0];
        int y = nonCandyPo[1];
        int id = nonCandyPo[2];
        if (id == 2)
            CellsVertex[x][y].setClickable(ClickableFactory::makeIcing(static_cast<IcingStatus>(id - 1)));
        else if (id == 3)
            CellsVertex[x][y].setClickable(ClickableFactory::makeWall());
    }
    
}


void Board::reset() {  
    // reset the board
    for (auto &row: CellsVertex) {
        for (auto &cell: row) {
            cell.setClickable(ClickableFactory::generateCandy(CandySpeciality::NONE));
        }
    }
    while (checkMatches());
};

void Board::draw() {
    for (auto &cellRow: CellsVertex) {
        for (auto &cell: cellRow) {
            cell.draw();
        }
    }
}

void Board::handleBoardDrag(Point p1, Point p2) {
    setAcceptInput(false);

    unHighlightAll();
    selectedCell = getCellFromPosition(p1);
    Cell *secondCell = getCellFromPosition(p2);
    if ((selectedCell && secondCell) && (isCandy(selectedCell) && isCandy(selectedCell))) {
        selectedCellCenter = selectedCell->getCenter();
        selectedCellPosition = p1;
        swapCells(secondCell, p2);
    }
    
    setAcceptInput(true);
}

Cell *Board::getCellFromPosition(Point p) {
    return &CellsVertex[p.x][p.y];
}

bool Board::handleBoardContains(Point p) {
    unHighlightAll();
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
    for (auto &row: CellsVertex) {
        for (auto &cell: row) {
            if (cell.contains(p)) return &cell;
        }
    }
    return nullptr;
}
 
Point Board::getPositionOfCell(Point p) {
    for (int i = 0; i < (int) CellsVertex.size(); ++i) {
        for (int j = 0; j < (int) CellsVertex[i].size(); ++j) {
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
    selectedCellCenter = getPositionOfCell(p);
}

void Board::setSwapCell(Cell *newCell) {
    toSwapCell = newCell;
}

void Board::setSwapCellPosition(Point p) {
    toSwapCellPosition = getPositionOfCell(p);
}

void Board::setCellAt(CandySpeciality newSpeciality, Color newColor, int i, int j) {
    CellsVertex[i][j].setClickable(ClickableFactory::makeCandy(newSpeciality, newColor));
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
    while (checkMatches());
}

void Board::resetHighlighting() {
    //Remove highlighting if an highlight is shown and the user clicks it while the cell is highlighted
    for (auto &cell: suggestedCells)
        cell->resetHighlight();
}

void Board::swapCells(Cell *swapCell, Point swapCellPosition) {
    setAcceptInput(false);
    runSuggestionThread = false;
    if (isMoveAllowed(selectedCellPosition, swapCellPosition)) {
        if (isCandy(selectedCell) && isCandy(swapCell) && !selectedCell->isEmpty() && !swapCell->isEmpty()) {
            resetHighlighting();
            suggestedCells.clear();
            exchangeCells(selectedCell, swapCell);
            if (checkForCandiesInteraction(selectedCell, selectedCellPosition, swapCell, swapCellPosition)) {
                while (checkMatches());
                while (checkIfShuffleIsNeeded()) {setShuffling(true); shuffle(); setShuffling(false); }
                decreaseMovesLeft();

            } else if (!checkMatches()) {
                //No matches found so exchange cells
                exchangeCells(selectedCell, swapCell);
            } else {
                while (checkMatches());
                while (checkIfShuffleIsNeeded()) {setShuffling(true); shuffle(); setShuffling(false);}
                decreaseMovesLeft();
            }
        }
    }
    runSuggestionThread = true;
    thread t1(&Board::handleSuggestionThread, this);
    t1.detach();
    selectedCell = nullptr;
    setAcceptInput(true);
}



void Board::handleSuggestionThread() {
    int t1 = 0;
    // check every half seconds whether the thread should still run or not
    while (runSuggestionThread && t1 < 4000) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        t1 += 500;
    }
    if (!runSuggestionThread) return;

    try {
        // highlight the suggested cells
        Cell *tempCell = suggestedCells.at(0);
        Cell *tempSwapCell = suggestedCells.at(1);
        tempCell->setHighlightColor(FL_RED);
        tempSwapCell->setHighlightColor(FL_RED);
        tempCell->setSuggestion(true);
        tempSwapCell->setSuggestion(true);

        int t2 = 0;
        while (runSuggestionThread && t2 < 2000) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            t2 += 500;
        }
        if (!runSuggestionThread) return;

        tempCell->resetHighlight();
        tempSwapCell->resetHighlight();
    }
    catch (const std::out_of_range &e) {
        return;
    }
    handleSuggestionThread();
}

bool Board::checkIfShuffleIsNeeded() {
    vector<array<int, 2>> deltas = {{0,  1},
                                    {1,  0},
                                    {0,  -1},
                                    {-1, 0}};
    for (int i = 0; i < (int) CellsVertex.size(); ++i) {
        for (int j = 0; j < (int) CellsVertex[i].size(); ++j) {
            Cell *tempCell = &CellsVertex[i][j];
            for (auto d: deltas) {
                try {
                    int dx = d[0];
                    int dy = d[1];
                    Cell *tempSwapCell = &CellsVertex.at(i + dy).at(j + dx);
                    if (!(tempSwapCell)->isEmpty()) {
                        //Swap two cells without animating to see if there are any
                        //If there are none, a shuffle is needed
                        //The first match found is used to suggest a move
                        swapCellsNoAnim(tempCell, tempSwapCell);
                        setHandleMatch(false);
                        if (checkMatches()) {
                            swapCellsNoAnim(tempCell, tempSwapCell);
                            setHandleMatch(true);
                            suggestedCells.push_back(tempCell);
                            suggestedCells.push_back(tempSwapCell);
                            return false;
                        }
                        swapCellsNoAnim(tempCell, tempSwapCell);
                    }
                }
                catch (out_of_range &e) {
                    continue;
                }
            }
        }
    }
    setHandleMatch(true);
    return true;
}

void Board::swapCellsNoAnim(Cell *cell1, Cell *cell2) {
    if (isCandy(cell1) && isCandy(cell2)) {
        Candy firstCellCandy = *cell1->getCandy();
        cell1->setClickable(*cell2->getCandy());
        cell2->setClickable(firstCellCandy);
    }
}

void Board::exchangeCells(Cell *cell1, Cell *cell2) {
    if (isCandy(cell1) && isCandy(cell2)) {
        cell1->animateCandy(cell2);
        Candy _selectedCellCandy = *cell1->getCandy();
        Point _selectedCellCenter = cell1->getCenter();

        cell1->setClickable(*cell2->getCandy());
        cell2->setClickable(_selectedCellCandy);

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

void Board::matchIcingObjective() {

    if (isObjective(Objective::CLEAR_ICING)) {
        int size = sqrt(numberOfCells) - 1;
        int i = 0;
        //Generate as many icing as objective and add 2 for good measure
        while (i <= getRemainingObjective() + 2) {
            int x1 = rand() % size;
            int y1 = rand() % size;
            if (!isIcing(CellsVertex[x1][y1])) {
                CellsVertex[x1][y1].setClickable(
                    ClickableFactory::makeIcing(static_cast<IcingStatus>(rand() % 2))
                );
            }
            i++;
        }
    }
}