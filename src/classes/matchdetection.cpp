#include "matchdetection.h"

MatchDetection::MatchDetection(Board *board) : candyBoard{board} {}

const int MatchDetection::matchFive[2][2][4] =
        {
                {{0,  0,  0, 0}, {-2, -1, 1, 2}},
                {{-2, -1, 1, 2}, {0,  0,  0, 0}}
        };

const int MatchDetection::wrappedCandy[6][2][2] =
        {
                {{-1, 1},  {-1, 1}},
                {{-1, -2}, {-1, 1}},
                {{1,  2},  {-1, 1}},
                {{-1, 1},  {1,  2}},
                {{1,  2},  {1,  2}},
                {{-1, -2}, {-1, -2}}
        };

const int MatchDetection::matchHorizontalFour[2][3] =
        {
                {-2, -1, 1},
                {-1, 1,  2}
        };

const int MatchDetection::matchVerticalFour[2][3] =
        {
                {-2, -1, 1},
                {-1, 1,  2}
        };

const int MatchDetection::matchHorizontal[2][3] =
        {
                {0,  0, 0},
                {-1, 0, 1}
        };

const int MatchDetection::matchVertical[2][3] =
        {
                {-1, 0, 1},
                {0,  0, 0}
        };

Color MatchDetection::getCellColor(int i, int j) {
    return CellsVertex.at(i).at(j).getColor();
}

bool MatchDetection::cellsColorMatch(int i, int j) {
    return currentCellColor == getCellColor(i, j);
}

bool MatchDetection::checkMatches() {
    CellsVertex = candyBoard->getCells();
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            currentCellColor = CellsVertex[i][j].getColor();
            if (checkMatchFive(i, j, currentCellColor)) return true;
            if (checkWrappedCandy(i, j, currentCellColor)) return true;
            if (checkHorizontalMatchFour(i, j, currentCellColor)) return true;
            if (checkVerticalMatchFour(i, j, currentCellColor)) return true;
        }
    }

    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            currentCellColor = CellsVertex[i][j].getColor();
            if (checkHorizontalMatch(i, j, currentCellColor)) return true;
            if (checkVerticalMatch(i, j, currentCellColor)) return true;
        }
    }
    return false;
}

bool MatchDetection::checkMatchFive(int i, int j) {
    unsigned long int array_size = sizeof(matchFive) / sizeof(matchFive[0]);
    for (int iterator = 0; iterator < array_size; iterator++) {
        try {
            const int *thisMatchI = matchFive[iterator][0];
            const int *thisMatchJ = matchFive[iterator][1];

            if (cellsColorMatch(i + thisMatchI[0], j + (thisMatchJ[0])) &&
                cellsColorMatch(i + thisMatchI[1], j + (thisMatchJ[1])) &&
                cellsColorMatch(i + thisMatchI[2], j + (thisMatchJ[2])) &&
                cellsColorMatch(i + thisMatchI[3], j + (thisMatchJ[3]))) {
                vector<vector<int>> cellsToRemove{
                        {i + thisMatchI[0], j + thisMatchJ[0]},
                        {i + thisMatchI[1], j + thisMatchJ[1]},
                        {i + thisMatchI[2], j + thisMatchJ[2]},
                        {i + thisMatchI[3], j + thisMatchJ[3]}};
                candyBoard->createSpecialCandy(i, j, CandySpeciality::MULTICOLOR);
                candyBoard->moveCells(cellsToRemove);
                return true;
            }

        }
        catch (const std::out_of_range &e) {
            return false;
        }
    }
    return false;

}

bool MatchDetection::checkWrappedCandy(int i, int j) {
    unsigned long int array_size = sizeof(wrappedCandy) / sizeof(wrappedCandy[0]);
    for (int iterator = 0; iterator < array_size; iterator++) {
        try {
            const int *thisMatchI = wrappedCandy[iterator][0];
            const int *thisMatchJ = wrappedCandy[iterator][1];

            if (cellsColorMatch(i, j + thisMatchJ[0]) &&
                cellsColorMatch(i, j + thisMatchJ[1]) &&
                cellsColorMatch(i + thisMatchJ[0], j) &&
                cellsColorMatch(i + thisMatchJ[1], j)) {

                vector<vector<int>> cellsToRemove{{i,                 j + thisMatchJ[0]},
                                                  {i,                 j + thisMatchJ[1]},
                                                  {i + thisMatchI[0], j},
                                                  {i + thisMatchI[1], j}};

                candyBoard->createSpecialCandy(i, j, CandySpeciality::BOMB);
                candyBoard->moveCells(cellsToRemove);

                return true;

            }
        }
        catch (const std::out_of_range &e) {
            return false;
        }
    }
    return false;

}

bool MatchDetection::checkHorizontalMatchFour(int i, int j) {
    unsigned long int array_size = sizeof(matchHorizontalFour) / sizeof(matchHorizontalFour[0]);
    for (int iterator = 0; iterator < array_size; iterator++) {
        try {
            const int *thisMatch = matchHorizontalFour[iterator];
            if (cellsColorMatch(i, j + thisMatch[0]) &&
                cellsColorMatch(i, j + thisMatch[1]) &&
                cellsColorMatch(i, j + thisMatch[2])) {
                vector<vector<int>> cellsToRemove{{i, j + thisMatch[0]},
                                                  {i, j + thisMatch[1]},
                                                  {i, j + thisMatch[2]}};
                candyBoard->createSpecialCandy(i, j, CandySpeciality::STRIPED_HORIZONTAL);
                candyBoard->moveCells(cellsToRemove);
                return true;
            }
            iterator++;
        }
        catch (const std::out_of_range &e) {
            return false;
        }
    }
    return false;

}

bool MatchDetection::checkVerticalMatchFour(int i, int j) {
    unsigned long int array_size = sizeof(matchVerticalFour) / sizeof(matchVerticalFour[0]);
    for (int iterator = 0; iterator < array_size; iterator++) {
        const int *thisMatch = matchVerticalFour[iterator];
        try {
            if (cellsColorMatch(i + thisMatch[0], j) &&
                cellsColorMatch(i + thisMatch[1], j) &&
                cellsColorMatch(i + thisMatch[2], j)) {
                vector<vector<int>> cellsToRemove{{i + thisMatch[0], j},
                                                  {i + thisMatch[1], j},
                                                  {i + thisMatch[2], j}};
                candyBoard->createSpecialCandy(i, j, CandySpeciality::STRIPED_VERTICAL);
                candyBoard->moveCells(cellsToRemove);
                return true;
            }
        }
        catch (const std::out_of_range &e) {
            return false;
        }
    }
    return false;
}


bool MatchDetection::checkHorizontalMatch(int i, int j) {
    try {
        if (cellsColorMatch(i, j + matchHorizontal[1][0]) &&
            cellsColorMatch(i, j + matchHorizontal[1][2])) {
            vector<vector<int>> cellsToRemove{{i + matchHorizontal[0][0], j + matchHorizontal[1][0]},
                                              {i + matchHorizontal[0][1], j + matchHorizontal[1][1]},
                                              {i + matchHorizontal[0][2], j +
                                                                          matchHorizontal[1][2]}}; // order doesn't matter
            candyBoard->moveCells(cellsToRemove);
            return true;
        }
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}


bool MatchDetection::checkVerticalMatch(int i, int j) {
    try {
        if (cellsColorMatch(i + matchVertical[0][0], j) &&
            cellsColorMatch(i + matchVertical[0][2], j)) {
            vector<vector<int>> cellsToRemove{{i + matchVertical[0][0], j},
                                              {i + matchVertical[0][1], j},
                                              {i + matchVertical[0][2], j}}; // don't change order
            candyBoard->moveCells(cellsToRemove);
            return true;
        }
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}