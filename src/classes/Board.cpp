/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: Board.cpp
* Date: 13/01/2022
*/
        
#include "Board.h"

Board::Board(int cellSize, int margin, int numberOfCells) : cellSize(cellSize), numberOfCells(numberOfCells) {
    setMargin(margin);
    CellsVertex = LevelFactory::buildCellVector("levels/level_1.txt", margin, cellSize, numberOfCells);
    initializeLevel();
    getInitialHighScore();  
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
    
    for (auto &row: CellsVertex) {
        for (auto &cell: row) {
            cell.setClickable(ClickableFactory::generateCandy(CandySpeciality::NONE));
        }
    }
    while (checkMatches());
    CellsVertex[3][6].setClickable(ClickableFactory::makeCandy(BOMB, Color::BLUE));
    CellsVertex[4][6].setClickable(ClickableFactory::makeCandy(STRIPED_HORIZONTAL, Color::BLUE));

    
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


void Board::swapCells(Cell *swapCell, Point swapCellPosition) {
    setAcceptInput(false);
   // terminateSuggestionsThreads();
    if (isMoveAllowed(selectedCellPosition, swapCellPosition)) {
        for (auto &cell: suggestedCells) {
            cell->resetHighlight();
        }
        suggestedCells.clear();
        if (isCandy(selectedCell) && isCandy(swapCell) && !selectedCell->isEmpty() && !swapCell->isEmpty()) {
            exchangeCells(selectedCell, swapCell);
            if (checkForCandiesInteraction(selectedCell, selectedCellPosition, swapCell, swapCellPosition)) {
                while (checkMatches());
                while (checkIfShuffleIsNeeded()) {setShuffling(true); shuffle(); setShuffling(false); }
                decreaseMovesLeft();

            } else if (!checkMatches()) {
                exchangeCells(selectedCell, swapCell);
            } else {
                while (checkMatches());
                while (checkIfShuffleIsNeeded()) {setShuffling(true); shuffle(); setShuffling(false);}
                decreaseMovesLeft();
            }
        }
    }

    thread t1(&Board::handleSuggestionThread, this);
    suggestionThread = &t1;
    suggestionThread->detach();
    selectedCell = nullptr;
    setAcceptInput(true);
}


void Board::terminateSuggestionsThreads() {
    if (suggestionThread && suggestionThread->joinable()) {
            suggestionThread->~thread();
    }
    suggestionThread = nullptr;
    Fl::unlock();
}

void Board::handleSuggestionThread() {
    Fl::unlock();
    this_thread::sleep_for(4s);
    try {
        Cell *tempCell = suggestedCells.at(0);
        Cell *tempSwapCell = suggestedCells.at(1);
        tempCell->setHighlightColor(FL_RED);
        tempSwapCell->setHighlightColor(FL_RED);
        tempCell->setSuggestion(true);
        tempSwapCell->setSuggestion(true);
        
        this_thread::sleep_for(2s);
        Cell *tempCell1 = suggestedCells.at(0);
        Cell *tempSwapCell1 = suggestedCells.at(1);

        tempCell1->resetHighlight();
        tempSwapCell1->resetHighlight();
    }
    catch (const std::out_of_range &e) {
        return;
    }
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
        while (i < getRemainingObjective()) {
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