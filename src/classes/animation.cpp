#include "animation.h"

Animation::Animation() = default;

void Animation::moveCellsDown(vector<vector<int>> cellsToReplace, vector<vector<Cell>> *CellVector, int margin){
    for (auto &cellToReplace: cellsToReplace)
        (*CellVector)[cellToReplace[0]][cellToReplace[1]].setCandy(CandyFactory::generateEmptyCandy());

    for (int l = 0; l < (int) margin; ++l) {
        for (auto &cellToReplace: cellsToReplace) {
            int i = cellToReplace[0];
            int j = cellToReplace[1];
            // drops all candy one cell under then generates candy for top cell
            for (int k = i; k > 0; k--) {
                Point movingCenter{(*CellVector)[k - 1][j].getCenter().x,
                                   (*CellVector)[k - 1][j].getCenter().y + 1};
                (*CellVector)[k - 1][j].setCenter(movingCenter);
            }
        }
        Fl::wait(0.003);
    }
    for (auto &cellToReplace: cellsToReplace) {
        int i = cellToReplace[0];
        int j = cellToReplace[1];
        for (int k = i; k > 0; k--) {
            Point originalCenter{(*CellVector)[k - 1][j].getCenter().x,
                                 (*CellVector)[k - 1][j].getCenter().y - margin};
            (*CellVector)[k - 1][j].setCenter(originalCenter);
            (*CellVector)[k][j].setCandy((*CellVector)[k - 1][j].getCandy());
        }
        (*CellVector)[0][j].setCandy(CandyFactory::generateCandy(CandySpeciality::NONE));
    }
}


