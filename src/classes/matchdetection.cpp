#include "matchdetection.h"
#include "pthread.h"
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
        if (speciality == CandySpeciality::NONE) cellsToRemove.push_back({i, j});
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
    vector<vector<array<int,2>>> match{{{0,  -1}, {0,0}, {0, 1}},
                                        {{-1, 0}, {0,0}, {1, 0}}};
    for (auto &matchThree: match) {
        if (checkMatch(matchThree, i, j, CandySpeciality::NONE)) return true;
    }
    return false;
}

bool MatchDetection::checkForCandiesInteraction(Cell* firstCell, Point firstCellPosition, Cell* secondCell, Point secondCellPosition) {
    CellsVertex = candyBoard->getCells();
    CandySpeciality firstCandySpeciality = firstCell->getSpeciality();
    CandySpeciality secondCandySpeciality = secondCell->getSpeciality();
    Color firstCandyColor = firstCell->getColor();
    Color secondCandyColor = secondCell->getColor();

    if ((firstCandySpeciality == NONE && secondCandySpeciality == MULTICOLOR) ||
     (firstCandySpeciality == MULTICOLOR && secondCandySpeciality == NONE)) {
        
        Color colorToRemove = firstCandyColor != Color::MULTICOLOR ? firstCandyColor : secondCandyColor;
        Point multicolorPosition = firstCandyColor == Color::MULTICOLOR ? firstCellPosition : secondCellPosition;
        normalCandyAndMulticolorInteraction(colorToRemove, multicolorPosition);
        return true;
    }

    else if (((firstCandySpeciality == STRIPED_HORIZONTAL || firstCandySpeciality == STRIPED_VERTICAL)) && 
        ( secondCandySpeciality == STRIPED_HORIZONTAL || secondCandySpeciality == STRIPED_VERTICAL)) {
       
         doubleStripedOrWrappedInteraction(firstCellPosition, secondCellPosition, 0, 0);
        return true;
    }

    else if ( firstCandySpeciality == BOMB &&
            ( secondCandySpeciality == STRIPED_HORIZONTAL || secondCandySpeciality == STRIPED_VERTICAL) ||
            
            ((firstCandySpeciality == STRIPED_HORIZONTAL || firstCandySpeciality == STRIPED_VERTICAL) && 
             secondCandySpeciality == BOMB))
        
        {
        doubleStripedOrWrappedInteraction(firstCellPosition, secondCellPosition, -1, 1);
        return true;
    }
    else if (firstCandySpeciality == BOMB && secondCandySpeciality == BOMB) {
        doubleWrappedInteraction(firstCellPosition, secondCellPosition);
        return true;
    }

    else if (((firstCandySpeciality == STRIPED_HORIZONTAL || firstCandySpeciality == STRIPED_VERTICAL) && secondCandySpeciality == MULTICOLOR) || 
              (firstCandySpeciality == MULTICOLOR && (secondCandySpeciality == STRIPED_VERTICAL || secondCandySpeciality == STRIPED_HORIZONTAL))) {
            Color colorToStripe = firstCandyColor != Color::MULTICOLOR ? firstCandyColor : secondCandyColor;
            
            stripedMulticolorInteraction(firstCellPosition, secondCellPosition, colorToStripe);
        return true;
    }

    else if ((firstCandySpeciality == BOMB && secondCandySpeciality == MULTICOLOR) || ( firstCandySpeciality == BOMB && secondCandySpeciality == MULTICOLOR)) {
        Color colorToWrap = firstCandyColor != Color::MULTICOLOR ? firstCandyColor : secondCandyColor;
        wrappedAndMulticolorInteraction(firstCellPosition, secondCellPosition, colorToWrap);
        return true;
    }

    else if (( firstCandySpeciality == MULTICOLOR && secondCandySpeciality == MULTICOLOR)) {
        doubleMulticolorInteraction();
        return true;
    }
    return false;
}


void MatchDetection::normalCandyAndMulticolorInteraction(Color colorToRemove, Point multicolorPosition) {
    candyBoard->moveCells(vector<vector<int>>({{multicolorPosition.x, multicolorPosition.y}}));
    Animation::emptyCell(&CellsVertex, multicolorPosition.x, multicolorPosition.y);
    std::cout << (int) colorToRemove;
    std::cout.flush();
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
    
            if (CellsVertex[i][j].getColor() == colorToRemove ) {
                candyBoard->moveCells(vector<vector<int>>({{i,j}}));
            }
        }
    }
}

void MatchDetection::doubleStripedOrWrappedInteraction(Point firstCellPosition, Point secondCellPosition, int leftOffset, int rightOffset) {
    for (int offset = leftOffset; offset <= rightOffset; offset++) {
        Animation::handleStrippedHorizontal(candyBoard.get(), &CellsVertex, firstCellPosition.x + offset, firstCellPosition.y);
    }
    for (int offset = leftOffset; offset <= rightOffset; offset++) {
        Animation::handleStrippedVertical(candyBoard.get(), &CellsVertex, firstCellPosition.x, firstCellPosition.y + offset);      
    }
    
}


void MatchDetection::doubleWrappedInteraction(Point firstCellPosition, Point secondCellPosition) {
    Animation::handleWrapped(candyBoard.get(), &CellsVertex, firstCellPosition.x, firstCellPosition.y, -2, 2);
}

void MatchDetection::stripedMulticolorInteraction(Point firstCellPosition, Point secondCellPosition, Color colorToStripe) {
    candyBoard->moveCells(vector<vector<int>>{{firstCellPosition.x, firstCellPosition.y}, {secondCellPosition.x, secondCellPosition.y}});
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        vector<vector<int>> cellsToCrush;
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToStripe) { 
                candyBoard->setCellAt(static_cast<CandySpeciality>(rand() % 2 + 1), colorToStripe, i, j);      //Choose randomly between striped horizontal and vertical
                cellsToCrush.push_back({i,j});
            }
        }
        Fl::wait(0.3);
        candyBoard->moveCells(cellsToCrush);
    
    }
}


void MatchDetection::wrappedAndMulticolorInteraction(Point firstCellPosition, Point secondCellPosition, Color colorToWrap) {
    Animation::emptyCells(vector<vector<int>>{{firstCellPosition.x, firstCellPosition.y}, {secondCellPosition.x, secondCellPosition.y}}, &CellsVertex);
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        vector<vector<int>> cellsToCrush;
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToWrap) {
                CellsVertex[i][j].setCandy(CandyFactory::generateCandy(BOMB, colorToWrap));            
                cellsToCrush.push_back({i,j});
            }
         candyBoard->moveCells(cellsToCrush);
    
        }
    }
}

void MatchDetection::doubleMulticolorInteraction() {
    candyBoard->reset();
    std::cout << "Wait this is illegal :) \n";
    std::cout.flush();
}