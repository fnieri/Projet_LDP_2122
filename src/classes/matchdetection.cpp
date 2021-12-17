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
        if (speciality != CandySpeciality::NONE) candyBoard->createSpecialCandy(i, j, speciality);
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
    vector<vector<array<int, 2>>> match{{{0,  -1}, {0, 0}, {0, 1}},
                                        {{-1, 0},  {0, 0}, {1, 0}}};
    for (auto &matchThree: match) {
        if (checkMatch(matchThree, i, j, CandySpeciality::NONE)) return true;
    }
    return false;
}

bool MatchDetection::checkForCandiesInteraction(Cell *firstCell, Point firstCellPosition, Cell *secondCell,
                                                Point secondCellPosition) {
    CellsVertex = candyBoard->getCells();
    CandySpeciality firstCandySpeciality = firstCell->getSpeciality();
    CandySpeciality secondCandySpeciality = secondCell->getSpeciality();
    Color firstCandyColor = firstCell->getColor();
    Color secondCandyColor = secondCell->getColor();

    switch (firstCandySpeciality) {
        case NONE:
            switch (secondCandySpeciality) {
                case MULTICOLOR:
                    MultiColorInteractions(firstCellPosition, secondCellPosition,
                                           firstCandyColor, secondCandyColor, vector<CandySpeciality>{NONE});
                    return true;
                default:
                    return false;
            }
        case STRIPED_HORIZONTAL:
        case STRIPED_VERTICAL:
            switch (secondCandySpeciality) {
                case STRIPED_HORIZONTAL:
                case STRIPED_VERTICAL: {
                    doubleStripedOrWrappedInteraction(firstCellPosition, secondCellPosition, 0, 0);
                    return true;
                }
                case BOMB: {
                    doubleStripedOrWrappedInteraction(firstCellPosition, secondCellPosition, -1, 1);
                    return true;
                }
                case MULTICOLOR:
                    MultiColorInteractions(firstCellPosition, secondCellPosition,
                                           firstCandyColor, secondCandyColor,
                                           vector<CandySpeciality>{STRIPED_HORIZONTAL, STRIPED_VERTICAL});
                    return true;
                default:
                    return false;
            }
        case BOMB:
            switch (secondCandySpeciality) {
                case STRIPED_VERTICAL:
                case STRIPED_HORIZONTAL:
                    doubleStripedOrWrappedInteraction(firstCellPosition, secondCellPosition, -1, 1);
                    return true;
                case BOMB:
                    doubleWrappedInteraction(firstCellPosition, secondCellPosition);
                    return true;
                case MULTICOLOR:
                    MultiColorInteractions(firstCellPosition, secondCellPosition,
                                           firstCandyColor, secondCandyColor, vector<CandySpeciality>{BOMB});
                    return true;
                default:
                    return false;
            }
        case MULTICOLOR:
            vector<CandySpeciality> specialities;
            switch (secondCandySpeciality) {
                case NONE:
                    specialities = {NONE};
                    break;
                case STRIPED_HORIZONTAL:
                case STRIPED_VERTICAL:
                    specialities = {STRIPED_VERTICAL, STRIPED_HORIZONTAL};
                    break;
                case BOMB:
                    specialities = {BOMB};
                    break;
                case MULTICOLOR:
                    doubleMulticolorInteraction();
                    return true;
                default:
                    return false;

            }
            //This only occurs if first candy is multicolor because of break
            MultiColorInteractions(firstCellPosition, secondCellPosition,
                                   firstCandyColor, secondCandyColor, specialities);
            return true;
    }
    return false;
}

void MatchDetection::MultiColorInteractions(Point firstCellPosition, Point secondCellPosition, Color firstColor,
                                            Color secondColor, vector<CandySpeciality> specialities) {
    Color colorToHandle = firstColor != Color::MULTICOLOR ? firstColor : secondColor;
    //Firstly remove multicolor and other candy because they wont be removed after
    candyBoard->moveCells(vector<vector<int>>({{firstCellPosition.x,  firstCellPosition.y},
                                               {secondCellPosition.x, secondCellPosition.y}}));

    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        vector<vector<int>> cellsToCrush;
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToHandle) {

                candyBoard->setCellAt(static_cast<CandySpeciality>(rand() % specialities.size()), colorToHandle, i, j);
                //Choose randomly between specialities sent, this is done because of the striped case
                cellsToCrush.push_back({i, j});

            }
        }
        candyBoard->moveCells(cellsToCrush);
    }
}


void MatchDetection::normalCandyAndMulticolorInteraction(Color colorToRemove, Point multicolorPosition) {
    candyBoard->moveCells(vector<vector<int>>({{multicolorPosition.x, multicolorPosition.y}}));
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToRemove) {
                candyBoard->moveCells(vector<vector<int>>({{i, j}}));
            }
        }
    }
}

void
MatchDetection::doubleStripedOrWrappedInteraction(Point firstCellPosition, Point secondCellPosition, int leftOffset,
                                                  int rightOffset) {
    for (int offset = leftOffset; offset <= rightOffset; offset++) {
        vector<vector<int>> cellsToMove;
        Animation::handleStrippedHorizontal(candyBoard.get(), &CellsVertex, firstCellPosition.x + offset,
                                            firstCellPosition.y, cellsToMove);
    }
    for (int offset = leftOffset; offset <= rightOffset; offset++) {
        vector<vector<int>> cellsToMove;
        Animation::handleStrippedVertical(candyBoard.get(), &CellsVertex, firstCellPosition.x,
                                          firstCellPosition.y + offset, cellsToMove);
    }
}


void MatchDetection::doubleWrappedInteraction(Point firstCellPosition, Point secondCellPosition) {
    vector<vector<int>> cellsToMove;
    Animation::handleWrapped(candyBoard.get(), &CellsVertex, firstCellPosition.x, firstCellPosition.y, cellsToMove, -2,
                             2);
}

void
MatchDetection::stripedMulticolorInteraction(Point firstCellPosition, Point secondCellPosition, Color colorToStripe) {
    candyBoard->moveCells(vector<vector<int>>{{firstCellPosition.x,  firstCellPosition.y},
                                              {secondCellPosition.x, secondCellPosition.y}});
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        vector<vector<int>> cellsToCrush;
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToStripe) {
                candyBoard->setCellAt(static_cast<CandySpeciality>(rand() % 2 + 1), colorToStripe, i,
                                      j);      //Choose randomly between striped horizontal and vertical
                //Choose randomly between striped orientation
                cellsToCrush.push_back({i, j});
            }
        }
        Fl::wait(0.3);
        candyBoard->moveCells(cellsToCrush);

    }
}


void
MatchDetection::wrappedAndMulticolorInteraction(Point firstCellPosition, Point secondCellPosition, Color colorToWrap) {
    Animation::emptyCells(vector<vector<int>>{{firstCellPosition.x,  firstCellPosition.y},
                                              {secondCellPosition.x, secondCellPosition.y}}, &CellsVertex);
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        vector<vector<int>> cellsToCrush;
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].getColor() == colorToWrap) {
                CellsVertex[i][j].setCandy(CandyFactory::generateCandy(BOMB, colorToWrap));
                cellsToCrush.push_back({i, j});
            }
            candyBoard->moveCells(cellsToCrush);
        }
    }
}

void MatchDetection::doubleMulticolorInteraction() {
    candyBoard->reset();
}

bool MatchDetection::canStillPlay() {
    vector<vector<Cell>> CellsVector = candyBoard->getCells();
    vector<array<int, 2>> delta{
            {-1, 0},
            {0,  -1},
            {0,  1},
            {1,  0},
    };
    for (int i = 0; i < (int) CellsVector.size(); i++) {
        for (int j = 0; j < (int) CellsVector[i].size(); j++) {
            Point cellPoint1 = {i, j};
            Cell* cell1 = &CellsVector[cellPoint1.x][cellPoint1.y];;
            for (array<int, 2> d: delta) {
                Point cellPoint2 = {i + d[0], j + d[1]};
                try {
                    Cell* cell2 = &CellsVector.at(cellPoint2.x).at(cellPoint2.y);
                    if (candyBoard->isMoveAllowed(cellPoint1, cellPoint2)) {
                        candyBoard->swapCellsNoAnim(cell1, cell2);
                        if (candyBoard->checkMatches()) {
                            candyBoard->swapCellsNoAnim(cell1, cell2);
                            return true;
                        }
                        candyBoard->swapCellsNoAnim(cell1, cell2);
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