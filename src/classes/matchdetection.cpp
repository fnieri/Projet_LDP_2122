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


MatchDetection::MatchDetection(Board *board) : candyBoard{board} {}


void MatchDetection::checkMatches() {
    CellsVertex = candyBoard->getCells();
    // this->tempBoard = *board;
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            Color currentCellColor = CellsVertex[i][j].getColor(); 
            if (checkMatchFive(i, j, currentCellColor)) continue;
            if (checkWrappedCandy(i, j, currentCellColor)) continue;
            if (checkHorizontalMatchFour(i, j, currentCellColor)) continue;
            if (checkVerticalMatchFour(i, j, currentCellColor)) continue;
        }
    }
    
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            Color currentCellColor = CellsVertex[i][j].getColor(); 
            
            if (checkHorizontalMatch(i, j, currentCellColor)) continue;
            if (checkVerticalMatch(i, j, currentCellColor)) continue;

        }
    }
}

bool MatchDetection::checkMatchFive(int i, int j, Color currentCellColor) {
    int iterator = 0;
    unsigned long int array_size = sizeof(this->matchFive) / sizeof(this->matchFive[0]);
    for (iterator; iterator < array_size; iterator++) {
        try {
            const int* thisMatchI = this->matchFive[iterator][0];
            const int* thisMatchJ = this->matchFive[iterator][1];

            if (currentCellColor == CellsVertex[i + thisMatchI[0]].at(j + (thisMatchJ[0])).getColor() &&
                currentCellColor == CellsVertex[i + thisMatchI[1]].at(j + (thisMatchJ[1])).getColor() &&
                currentCellColor == CellsVertex[i + thisMatchI[2]].at(j + (thisMatchJ[2])).getColor() &&
                currentCellColor == CellsVertex[i + thisMatchI[3]].at(j + (thisMatchJ[3])).getColor()) {
           /* 
               if (CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 2).getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j - 1).getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 1).getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j + 2).getColor()) {
            */
                vector<vector<int>> cellsToRemove {
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
        iterator++;
    }
    return false;

}

bool MatchDetection::checkWrappedCandy(int i, int j, Color currentCellColor) {
    int iterator = 0;
    unsigned long int array_size = sizeof(this->wrappedCandy) / sizeof(this->wrappedCandy[0]);
    for (iterator; iterator < array_size; iterator++) {
       try {
            const int* thisMatchI = this->wrappedCandy[iterator][0];
            const int* thisMatchJ = this->wrappedCandy[iterator][1];

            if (currentCellColor == CellsVertex[i].at(j + thisMatchJ[0]).getColor() &&
                currentCellColor == CellsVertex[i].at(j + thisMatchJ[0]).getColor() &&
                currentCellColor == CellsVertex.at(i + thisMatchI[0])[j].getColor() &&
                currentCellColor == CellsVertex.at(i + thisMatchI[1])[j].getColor()) {
              
            vector<vector<int>> cellsToRemove {{i, j + thisMatchJ[0]},
                                 {i, j + thisMatchJ[1]},
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
        iterator++;
    }
    return false;

}

bool MatchDetection::checkHorizontalMatchFour(int i, int j, Color currentCellColor) {
    int iterator = 0;
    unsigned long int array_size = sizeof(this->matchHorizontalFour) / sizeof(this->matchHorizontalFour[0]);
    for (iterator; iterator < array_size; iterator++) {
      try {
            const int* thisMatch = this->matchHorizontalFour[iterator];
            if (currentCellColor ==
                CellsVertex[i].at(j + thisMatch[0]).getColor() &&
                currentCellColor ==
                CellsVertex[i].at(j + this->matchHorizontalFour[iterator][1]).getColor() &&
                currentCellColor ==
                CellsVertex[i].at(j + this->matchHorizontalFour[iterator][2]).getColor()) {
                vector<vector<int>> cellsToRemove{{i, j + matchHorizontalFour[iterator][0]},
                                 {i, j + this->matchHorizontalFour[iterator][1]},
                                 {i, j + this->matchHorizontalFour[iterator][2]}};
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

bool MatchDetection::checkVerticalMatchFour(int i, int j, Color currentCellColor) {
    int iterator = 0;
    unsigned long int array_size = sizeof(this->matchVerticalFour) / sizeof(this->matchVerticalFour[0]);
    for (iterator; iterator < array_size; iterator++) {
        const int* thisMatch = this->matchVerticalFour[iterator];  
        try {
            if (currentCellColor == CellsVertex.at(i + thisMatch[0])[j].getColor() &&
                currentCellColor == CellsVertex.at(i + thisMatch[1])[j].getColor() &&
                currentCellColor == CellsVertex.at(i + thisMatch[2])[j].getColor()) {
                vector<vector<int>> cellsToRemove{{i + this->matchVertical[0][0], j},
                                 {i + this->matchVertical[0][1], j},
                                 {i + this->matchVertical[0][2], j}};

                candyBoard->createSpecialCandy(i, j, CandySpeciality::STRIPED_VERTICAL);
                candyBoard->moveCells(cellsToRemove);
                return true;
            }
        }
        catch (const std::out_of_range &e) {
            return false;
        }
        iterator++;
    }
    return false;
}


bool MatchDetection::checkHorizontalMatch(int i, int j, Color currentCellColor) {
    try {
        if (CellsVertex[i].at(j + this->matchHorizontal[1][0]).getColor() == CellsVertex[i][j].getColor() &&
            CellsVertex[i][j].getColor() == CellsVertex[i].at(j + this->matchHorizontal[1][2]).getColor()) {
                            vector<vector<int>> cellsToRemove {{i + this->matchHorizontal[0][0], j + this->matchHorizontal[1][0]},
                                              {i + this->matchHorizontal[0][1], j + this->matchHorizontal[1][1]},
                                              {i + this->matchHorizontal[0][2], j + this->matchHorizontal[1][2]}}; // order doesn't matter
            candyBoard->moveCells(cellsToRemove);
            return true;
        }
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}


bool MatchDetection::checkVerticalMatch(int i, int j, Color currentCellColor) {
    try {
        if (CellsVertex.at(i - 1)[j].getColor() == currentCellColor &&
            CellsVertex[i][j].getColor() == CellsVertex.at(i + 1)[j].getColor()) {
            vector<vector<int>> cellsToRemove {{i + this->matchVertical[0][0], j},
                                              {i + this->matchVertical[0][1],     j},
                                              {i + this->matchVertical[0][2], j}}; // don't change order
            candyBoard->moveCells(cellsToRemove);
            return true;
        }
        return false;
    }
    catch (const std::out_of_range &e) {
        return false;
    }
}