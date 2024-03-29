/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: Game.cpp
* Date: 13/01/2022
*/
        
#include "Game.h"

bool Game::contains(Point p){
    for (int i = 0; i < (int)CellsVertex.size(); i++){
        for (int j = 0; j < (int)CellsVertex[i].size(); j++){
            if (CellsVertex[i][j].contains(p)){
                return true;
            }
        }
    }
    return false;
}

bool Game::remainingEmptyCells() {
    for (int i = 0; i < (int) CellsVertex.size(); i++) {
        for (int j = 0; j < (int) CellsVertex[i].size(); j++) {
            if (CellsVertex[i][j].isEmpty()) {
                return true;
            }
        }
    }
    return false;
}

void Game::gameWait(useconds_t time){
    if (!isInputAllowed() && !isResetting()){
        usleep(time);
        Fl::check();
    }
}

vector<vector<int>> Game::findEmptyCells() {
    vector<vector<int>> cellsToDrop;
    // find all empty cells in CellsVertex and drop them
    for (int col = 0; col < (int) CellsVertex.size(); ++col) {
        for (int row = 0; row < (int) CellsVertex[col].size(); ++row) {
            if (CellsVertex[col][row].isEmpty()) {
                cellsToDrop.push_back({col, row});
            }
        }
    }
    return cellsToDrop;
}

void Game::createSpecialCandy(int i, int j, CandySpeciality speciality){
    if (speciality == CandySpeciality::MULTICOLOR)
        CellsVertex[i][j].setClickable(
            ClickableFactory::makeCandy(speciality));
    else
        CellsVertex[i][j].setClickable(ClickableFactory::makeCandy(speciality, CellsVertex[i][j].getColor()));
}

void Game::highlight(Point p){
    for (auto &i : CellsVertex){
        for (auto &j : i){
            if (j.hasCandy() && !j.isEmpty() && j.contains(p))
                j.setHighlighted(true);
            else
                j.setHighlighted(false);
        }
    }
};

void Game::unHighlightAll(){
    for (auto &i : CellsVertex){
        for (auto &j : i){
            j.setHighlighted(false);
        }
    }
}

void Game::setMargin(int m){
    margin = m;
}

vector<vector<Cell>> Game::getCells(){
    return CellsVertex;
}

void Game::setAcceptInput(bool newState){
    acceptInput = newState;
}

bool Game::isInputAllowed(){
    return acceptInput;
}

void Game::addToScore(int scoreToAdd){
    score += scoreToAdd;
    saveHighscore();
}

//http://www.cplusplus.com/forum/beginner/195138/
//Check if  highscore can be saved each time score is incremented
void Game::saveHighscore(){
    if (score > hiScore)
    {
        hiScore = score;
        std::fstream bestScoreFile(BEST_SCORE_FILE);
        std::string currentBestScore;
        if (bestScoreFile.is_open())
        {
            //Save high score
            bestScoreFile << to_string(hiScore);
        }
        bestScoreFile.close();
    }
}

void Game::getInitialHighScore(){
    std::fstream bestScoreFile(BEST_SCORE_FILE);
    std::string currentBestScore;
    if (bestScoreFile.is_open())
    {
        std::getline(bestScoreFile, currentBestScore);
        if (currentBestScore.length() != 0)
            hiScore = stoi(currentBestScore);
        else {
            bestScoreFile << "0";
            hiScore = 0;
        }
    }
    
    else {
        //Create file if it doesn't exist, reopen and write 0 to it
        std::ofstream(BEST_SCORE_FILE);
        std::fstream bestScoreFile(BEST_SCORE_FILE);
        bestScoreFile << "0";
        hiScore = 0;
    }

    bestScoreFile.close();
}

int Game::getScore() {
    return score;
}

int Game::getMovesLeft() {
    return movesLeft;
}

bool Game::gameIsOver() {
    if (movesLeft <= 0) {
        setGameState(true);
        return true;
    }
    return false;
}

void Game::setGameState(bool newState) {
    gameOver = false;
}

void Game::decreaseMovesLeft() {
    if (!gameIsOver())
    movesLeft -= 1;
}

void Game::setMovesLeft(int newMoves) {
    movesLeft = newMoves;
}

void Game::resetGame() {
    setMovesLeft(30);
    setGameState(false);
    score = 0;

}

bool Game::isIcing(Cell cell) {return cell.hasIcing();}
    
bool Game::isCandy(Cell *cell) {return cell->hasCandy();}

bool Game::isCandy(Cell cell) {return cell.hasCandy();}

void Game::setShuffling(bool newState) {
    shuffling = newState;
}
bool Game::isShuffling() {
    return shuffling;
}

void Game::setResetting(bool newState) {
    resetting = newState;
}

bool Game::isResetting() {
    return resetting;
}