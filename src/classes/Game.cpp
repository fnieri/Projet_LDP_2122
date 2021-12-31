//
// Created by louis on 19/12/2021.
//

#include "Game.h"

bool Game::contains(Point p) {
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].contains(p)) {
                return true;
            }
        }
    }
    return false;
}

void Game::createSpecialCandy(int i, int j, CandySpeciality speciality) {
    if (speciality == CandySpeciality::MULTICOLOR)
        CellsVertex[i][j].setObject(
            ClickableFactory::makeCandy(speciality));
    else
        CellsVertex[i][j].setObject(ClickableFactory::makeCandy(speciality, CellsVertex[i][j].getColor()));
}

void Game::highlight(Point p) {
    for (auto &i: CellsVertex) {
        for (auto &j: i) {
            if (j.contains(p)) j.setHighlighted(true);
            else j.setHighlighted(false);
        }
    }
};

void Game::unHighlightAll() {
    for (auto &i: CellsVertex) {
        for (auto &j: i) {
            j.setHighlighted(false);
        }
    }
}

void Game::setMargin(int m) {
    margin = m;
}

vector<vector<Cell>> Game::getCells() {
    return CellsVertex;
}

void Game::setAcceptInput(bool newState){
    acceptInput = newState;
}

bool Game::isInputAllowed(){
    return acceptInput;
}
