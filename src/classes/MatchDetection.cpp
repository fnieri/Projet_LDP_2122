#include "MatchDetection.h"

Color MatchDetection::getCellColor(int i, int j) {
    if (isCandy(CellsVertex.at(i).at(j)))
        return CellsVertex.at(i).at(j).getColor();
}

bool MatchDetection::cellsColorMatch(int i, int j) {
    if (isCandy(CellsVertex.at(i).at(j))) 
        return currentCellColor == getCellColor(i, j);
    return false;
}

void MatchDetection::setHandleMatch(bool handleM) {
    handleMatch = handleM;
}

bool MatchDetection::checkMatches() {
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (isCandy(CellsVertex[i][j])) {
                currentCellColor = CellsVertex[i][j].getColor();
                if (checkMatchFive(i, j)) return true;
                if (checkWrappedCandy(i, j)) return true;
                if (checkHorizontalMatchFour(i, j)) return true;
                if (checkVerticalMatchFour(i, j)) return true;
            }         
        }
    }

    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (isCandy(CellsVertex[i][j])) {
                currentCellColor = CellsVertex[i][j].getColor();
                if (checkMatchThree(i, j)) return true;
            }
        }
    }
    return false;
}

bool MatchDetection::checkMatch(vector <array<int, 2>> match, int i, int j, CandySpeciality speciality) {
    vector <vector<int>> cellsToRemove;
    try {
        for (auto &matchArray: match) {
            int matchI = i + matchArray[0];
            int matchJ = j + matchArray[1];
            if (!cellsColorMatch(matchI, matchJ)) break;
            cellsToRemove.push_back({matchI, matchJ});
        }
    }
    catch (const out_of_range &e) {
        return false;
    }
    if (cellsToRemove.size() == match.size()) {
        if (handleMatch) {
            if (speciality != CandySpeciality::NONE) createSpecialCandy(i, j, speciality);
            handleCellsToReplace(cellsToRemove);
        }
        return true;
    }
    return false;
}

bool MatchDetection::checkWrappedCandy(int i, int j) {
    vector < vector < array < int, 2>>> match{{{1,  0}, {2,  0}, {0, 1},  {0, 2}},
                                              {{-1, 0}, {-2, 0}, {0, -1}, {0, -2}}};
    for (auto &matchWrapped: match) {
        if (checkMatch(matchWrapped, i, j, CandySpeciality::BOMB)) return true;
    }
    return false;
}

bool MatchDetection::checkMatchFive(int i, int j) {
    vector < vector < array < int, 2>>> match{{{0,  -1}, {0, 1}, {0, 2}, {0, 3}},
                                              {{-1, 0},  {1, 0}, {2, 0}, {3, 0}}};
    for (auto &matchFive: match) {
        if (checkMatch(matchFive, i, j, CandySpeciality::MULTICOLOR)) return true;
    }
    return false;
}

bool MatchDetection::checkHorizontalMatchFour(int i, int j) {
    vector <array<int, 2>> match{{0, -1},
                                 {0, 1},
                                 {0, 2}};
    return checkMatch(match, i, j, CandySpeciality::STRIPED_VERTICAL);
}

bool MatchDetection::checkVerticalMatchFour(int i, int j) {
    vector <array<int, 2>> match{{-1, 0},
                                 {1,  0},
                                 {2,  0}};
    return checkMatch(match, i, j, CandySpeciality::STRIPED_HORIZONTAL);
}

bool MatchDetection::checkMatchThree(int i, int j) {
    vector < vector < array < int, 2>>> match{{{0,  -1}, {0, 0}, {0, 1}},
                                              {{-1, 0},  {0, 0}, {1, 0}}};
    for (auto &matchThree: match) {
        if (checkMatch(matchThree, i, j, CandySpeciality::NONE)) return true;
    }
    return false;
}



bool MatchDetection::canStillPlay() {
    vector <vector<Cell>> CellsVector = getCells();
    vector <array<int, 2>> delta{
            {-1, 0},
            {0,  -1},
            {0,  1},
            {1,  0},
    };
    for (int i = 0; i < (int) CellsVector.size(); i++) {
        for (int j = 0; j < (int) CellsVector[i].size(); j++) {
            Point cellPoint1 = {i, j};
            Cell *cell1 = &CellsVector[cellPoint1.x][cellPoint1.y];;
            for (array<int, 2> d: delta) {
                Point cellPoint2 = {i + d[0], j + d[1]};
                try {
                    Cell *cell2 = &CellsVector.at(cellPoint2.x).at(cellPoint2.y);
                    if (isCandy(cell1) && isCandy(cell2)) {
                        if (isMoveAllowed(cellPoint1, cellPoint2)) {
                            swapCellsNoAnim(cell1, cell2);
                            if (checkMatches()) {
                                swapCellsNoAnim(cell1, cell2);
                                return true;
                            }
                            swapCellsNoAnim(cell1, cell2);
                        }
                    }
                }
                catch (const out_of_range &oor) {
                    continue;
                }
            }
        }
    }
    return false;
};

bool MatchDetection::checkForCandiesInteraction(Cell *firstCell, Point firstCellPosition, Cell *secondCell,
                                                Point secondCellPosition) {
    CandySpeciality firstCandySpeciality = firstCell->getSpeciality();
    CandySpeciality secondCandySpeciality = secondCell->getSpeciality();
    Color firstCandyColor = firstCell->getColor();
    Color secondCandyColor = secondCell->getColor();

    // call it twice with reversed arguments instead of having a long switch-case
    if (doubleSpecialCandyInteraction(firstCellPosition, secondCellPosition, firstCandyColor, secondCandyColor,
                                      firstCandySpeciality, secondCandySpeciality))
        return true;
    else
        return doubleSpecialCandyInteraction(secondCellPosition, firstCellPosition, secondCandyColor, firstCandyColor,
                                             secondCandySpeciality, firstCandySpeciality);

}