#include "matchdetection.h"

MatchDetection::MatchDetection(Board *board) : candyBoard{board} {}

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
            if (checkMatchFive(i, j)) return true;
            if (checkWrappedCandy(i, j)) return true;
            if (checkHorizontalMatchFour(i, j)) return true;
            if (checkVerticalMatchFour(i, j)) return true;
        }
    }
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            currentCellColor = CellsVertex[i][j].getColor();
            if (checkMatchThree(i, j)) return true;
        }
    }
    return false;
}

bool MatchDetection::checkMatch(vector<array<int, 2>> match, int i, int j, CandySpeciality speciality) {
    vector<vector<int>> cellsToRemove;
    try {
        for (auto &matchArray: match) {
            int matchI = i + matchArray[0];
            int matchJ = j + matchArray[1];
            if (!cellsColorMatch(matchI, matchJ)) break;
            cellsToRemove.push_back({matchI, matchJ});
        }
    }
    catch (const std::out_of_range &e) {
        return false;
    }
    if (cellsToRemove.size() == match.size()) {
        if (speciality == CandySpeciality::NONE) cellsToRemove.insert(cellsToRemove.begin()+1, {i, j});
        else candyBoard->createSpecialCandy(i, j, speciality);
        candyBoard->moveCells(cellsToRemove);
        return true;
    }
    return false;
}

bool MatchDetection::checkWrappedCandy(int i, int j) {
    vector<vector<array<int, 2>>> match{{{1,  0}, {2,  0}, {0, 1},  {0, 2}},
                                        {{-1, 0}, {-2, 0}, {0, -1}, {0, -2}}};
    for (auto &matchWrapped: match) {
        if (checkMatch(matchWrapped, i, j, CandySpeciality::BOMB)) return true;
    }
    return false;
}

bool MatchDetection::checkMatchFive(int i, int j) {
    vector<vector<array<int, 2>>> match{{{0,  -1}, {0, 1}, {0, 2}, {0, 3}},
                                        {{-1, 0},  {1, 0}, {2, 0}, {3, 0}}};
    for (auto &matchFive: match) {
        if (checkMatch(matchFive, i, j, CandySpeciality::MULTICOLOR)) return true;
    }
    return false;
}

bool MatchDetection::checkHorizontalMatchFour(int i, int j) {
    vector<array<int, 2>> match{{0, -1},
                                {0, 1},
                                {0, 2}};
    return checkMatch(match, i, j, CandySpeciality::STRIPED_VERTICAL);
}

bool MatchDetection::checkVerticalMatchFour(int i, int j) {
    vector<array<int, 2>> match{{-1, 0},
                                {1,  0},
                                {2,  0}};
    return checkMatch(match, i, j, CandySpeciality::STRIPED_HORIZONTAL);
}

bool MatchDetection::checkMatchThree(int i, int j) {
    vector<vector<array<int, 2>>> match{{{0, -1}, {0,  1}},
                                        {{-1, 0},  {1, 0}}};
    for (auto &matchThree: match) {
        if (checkMatch(matchThree, i, j, CandySpeciality::NONE)) return true;
    }
    return false;
}