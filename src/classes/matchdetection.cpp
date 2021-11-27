//
// Created by frann on 27/11/21.
//

#include "matchdetection.h"
const int MatchDetection::matchFive[2][2][4] = 
    {
        {{0, 0, 0, 0}, {-2, -1, 1, 2}},
        {{-2, -1, 1, 2}, {0, 0, 0, 0}}
    };

const int MatchDetection::wrappedCandy[6][2][2] = 
    {
            {{-1, 1}, {-1, 1}},
            {{-1, -2}, {-1, 1}},
            {{1, 2}, {-1, 1}},
            {{-1, 1}, {1, 2}},
            {{1, 2}, {1, 2}},
            {{-1, -2}, {-1, -2}}
    };

const int MatchDetection::matchHorizontalFour[2][3] =
    {
        {-2, -1, 1}, {-1, 1, 2}
    };

const int MatchDetection::matchVerticalFour[2][3] =
    {
            {-2, -1, 1}, {-1, 1, 2}
    };

const int MatchDetection::matchHorizontal[2][3] =
    {
            {0, 0, 0}, {-1, 0, 1}
    };

const int MatchDetection::matchVertical[2][3] =
    {
        {-1, 0, 1}, {0, 0, 0}
    };


bool MatchDetection::checkForCandiesInteraction(Candy firstCandy, Candy secondCandy) {
    return true;
}


MatchDetection::MatchDetection(Board board) : candyBoard{board} {
    
}
void MatchDetection::checkMatches(Board board) {
    this->candyBoard = board;
    this->CellsVertex = candyBoard.getCells();

}
bool MatchDetection::checkMatchFive(int i, int j) {
    try {
        int iterator = 0;
        while (iterator < sizeof(this->matchFive) / sizeof(this->matchFive[0][0][0])) {
            if (CellsVertex[i][j].getColor() == CellsVertex[i + this->matchFive[iterator][0][0]].at(j + this->matchFive[iterator][1][0]).getColor() &&
                CellsVertex[i][j].getColor() == CellsVertex[i + this->matchFive[iterator][0][1]].at(j - this->matchFive[iterator][1][1]).getColor() &&
                CellsVertex[i][j].getColor() == CellsVertex[i + this->matchFive[iterator][0][2]].at(j + this->matchFive[iterator][1][2]).getColor() &&
                CellsVertex[i][j].getColor() == CellsVertex[i + this->matchFive[iterator][0][3]].at(j + this->matchFive[iterator][1][3]).getColor()) {
                cellsToRemove = {
                        {i + this->matchFive[iterator][0][0], j + this->matchFive[iterator][1][0]},
                        {i + this->matchFive[iterator][0][1], j + this->matchFive[iterator][1][1]},
                        {i + this->matchFive[iterator][0][2], j + this->matchFive[iterator][1][2]},
                        {i + this->matchFive[iterator][0][3], j + this->matchFive[iterator][1][3]}};
                candyBoard.createSpecialCandy(i, j, CandySpeciality::BOMB);
                candyBoard.moveCells(cellsToRemove);
                return true;
                }
            iterator++;
            }
            return false;
        }
    catch (const std::out_of_range &e) {
        return false;
    }
}

bool MatchDetection::checkWrappedCandy(int i, int j) {
    int iterator = 0;
    try {
        while (iterator < sizeof(this->wrappedCandy) / sizeof(this->wrappedCandy[0][0][0])) {

            if (CellsVertex[i][j].getColor() == CellsVertex[i].at(j + this->wrappedCandy[iterator][1][0]).getColor() &&
                CellsVertex[i][j].getColor() == CellsVertex[i].at(j + this->wrappedCandy[iterator][1][0]).getColor() &&
                CellsVertex[i][j].getColor() == CellsVertex.at(i + this->wrappedCandy[iterator][0][0])[j].getColor() &&
                CellsVertex[i][j].getColor() == CellsVertex.at(i + this->wrappedCandy[iterator][0][1])[j].getColor()) {
                cellsToRemove = {{i, j + this->wrappedCandy[iterator][1][0]},
                                 {i, j + this->wrappedCandy[iterator][1][1]},
                                 {i + this->wrappedCandy[iterator][0][0], j},
                                 {i + this->wrappedCandy[iterator][0][1], j}};
                return true;

                candyBoard.createSpecialCandy(i, j, CandySpeciality::STRIPED_BOMB);
                candyBoard.moveCells(cellsToRemove);
            }
            iterator++;
        }
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}

bool MatchDetection::checkHorizontalMatchFour(int i, int j) {
    int iterator = 0;
    try {
        while (iterator < sizeof(this->matchHorizontalFour) / sizeof(this->matchHorizontalFour[0][0])) {
            if (CellsVertex[i][j].getColor() ==
                CellsVertex[i].at(j + this->matchHorizontalFour[iterator][0]).getColor() &&
                CellsVertex[i][j].getColor() ==
                CellsVertex[i].at(j + this->matchHorizontalFour[iterator][1]).getColor() &&
                CellsVertex[i][j].getColor() ==
                CellsVertex[i].at(j + this->matchHorizontalFour[iterator][2]).getColor()) {
                cellsToRemove = {{i, j + matchHorizontalFour[iterator][0]},
                                 {i, j - 1},
                                 {i, j + 1}};
                candyBoard.createSpecialCandy(i, j, CandySpeciality::STRIPED_HORIZONTAL);
                candyBoard.moveCells(cellsToRemove);
                return true;
            }
        iterator++;
        }
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}

bool MatchDetection::checkVerticalMatchFour(int i, int j) {
    vector<vector<Cell>> CellsVertex = candyBoard.getCells();
    int iterator = 0;
    try {
        while (iterator < sizeof(this->matchVerticalFour) / sizeof(this->matchVerticalFour[0][0])) {
            if (CellsVertex[i][j].getColor() ==
                CellsVertex.at(i + this->matchVerticalFour[iterator][0])[j].getColor() &&
                CellsVertex[i][j].getColor() == CellsVertex.at(i + this->matchVerticalFour[iterator][1])[j].getColor() &&
                CellsVertex[i][j].getColor() == CellsVertex.at(i + this->matchVerticalFour[iterator][2])[j].getColor()) {
                cellsToRemove = {{i + this->matchVertical[0][0], j},
                                 {i + this->matchVertical[0][1], j},
                                 {i + this->matchVertical[0][2], j}};

                candyBoard.createSpecialCandy(i, j, CandySpeciality::STRIPED_VERTICAL);
                candyBoard.moveCells(cellsToRemove);
                return true;
            }
        iterator++;
        }
    }
    catch (const std::out_of_range &e) {
        return false;

    }
}


bool MatchDetection::checkHorizontalMatch(int i, int j) {

    try {
        if (CellsVertex[i].at(j + this->matchHorizontal[1][0]).getColor() == CellsVertex[i][j].getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j + this->matchHorizontal[1][2]).getColor()) {
                            cellsToRemove =   {{i + this->matchHorizontal[0][0], j + this->matchHorizontal[1][0]},
                                              {i + this->matchHorizontal[0][1], j + this->matchHorizontal[1][1]},
                                              {i + this->matchHorizontal[0][2], j + this->matchHorizontal[1][2]}}; // order doesn't matter
            candyBoard.moveCells(cellsToRemove);
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
        if (CellsVertex.at(i - 1)[j].getColor() == CellsVertex[i][j].getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex.at(i + 1)[j].getColor()) {
            cellsToRemove = {{i + this->matchVertical[0][0], j},
                                              {i + this->matchVertical[0][1],     j},
                                              {i + this->matchVertical[0][2], j}}; // don't change order
            candyBoard.moveCells(cellsToRemove);
            return true;
        }
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}