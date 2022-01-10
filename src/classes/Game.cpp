//
// Created by louis on 19/12/2021.
//

#include "Game.h"

bool Game::contains(Point p)
{
    for (int i = 0; i < (int)CellsVertex.size(); i++)
    {
        for (int j = 0; j < (int)CellsVertex[i].size(); j++)
        {
            if (CellsVertex[i][j].contains(p))
            {
                return true;
            }
        }
    }
    return false;
}

void Game::createSpecialCandy(int i, int j, CandySpeciality speciality)
{
    if (speciality == CandySpeciality::MULTICOLOR)
        CellsVertex[i][j].setClickable(
            ClickableFactory::makeCandy(speciality));
    else
        CellsVertex[i][j].setClickable(ClickableFactory::makeCandy(speciality, CellsVertex[i][j].getColor()));
}

void Game::highlight(Point p)
{
    for (auto &i : CellsVertex)
    {
        for (auto &j : i)
        {
            if (j.contains(p))
                j.setHighlighted(true);
            else
                j.setHighlighted(false);
        }
    }
};

void Game::unHighlightAll()
{
    for (auto &i : CellsVertex)
    {
        for (auto &j : i)
        {
            j.setHighlighted(false);
        }
    }
}

void Game::setMargin(int m)
{
    margin = m;
}

vector<vector<Cell>> Game::getCells()
{
    return CellsVertex;
}

void Game::setAcceptInput(bool newState)
{
    acceptInput = newState;
}

bool Game::isInputAllowed()
{
    return acceptInput;
}

void Game::addToScore(int scoreToAdd)
{
    score += scoreToAdd;
    saveHighscore();
}

//http://www.cplusplus.com/forum/beginner/195138/
void Game::saveHighscore()
{
    if (score > hiScore)
    {
        hiScore = score;
        //Trunc is to remove all content
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

void Game::getInitialHighScore()
{
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
        //Create file if it doesn't exist and reopen
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

void Game::setAnimating(bool newState) {
    animating = newState;
}

bool Game::isAnimating(){
    return animating;
}

void Game::setShuffling(bool newState) {
    shuffling = newState;
}
bool Game::isShuffling() {
    //Every day i'm shuffling
    return shuffling;
}


void Game::setResetting(bool newState) {
    resetting = newState;
}

bool Game::isResetting() {
    return resetting;
}