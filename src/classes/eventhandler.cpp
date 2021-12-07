#include "eventhandler.h"

EventHandler::EventHandler(Board *board) : board{board} {}
Point EventHandler::getFirstPosition()
{
    return firstPosition;
}

Point EventHandler::getSecondPosition()
{
    return secondPosition;
}

void EventHandler::setFirstPosition(Point p)
{
    firstPosition = board->getPositionOfCell(p);
}

void EventHandler::setSecondPosition(Point p)
{
    secondPosition = board->getPositionOfCell(p);
}

void EventHandler::handleDrag(Point p)
{

    if (!(p.x < 0) && !(p.y < 0))
    {

        if (firstPosition == Point{-1, -1})
        {
            this->setSelectedCell(p);
        }
        else
        {
            setSecondPosition(p);
            if (getSecondPosition() != getFirstPosition())
            {

                board->setAcceptInput(false);
                board->swapCells(board->cellAt(p), secondPosition);
                this->reset(); //Pls don't hurt me it's to recognise board reset and this reset
            
            }
            else
            {
                setFirstPosition(p);
            }
        }
    }
}

void EventHandler::setSelectedCell(Point p) {
    
    setFirstPosition(p);
    board->setSelectedCell(board->cellAt(p));
    board->setSelectedCellPosition(p);    
}


void EventHandler::setSwapCell(Point p) {
    
    board->setSwapCell(board->cellAt(p));
    board->setSwapCellPosition(p);                
}

void EventHandler::reset()
{
    firstPosition = Point{-1, -1};
    secondPosition = Point{-1, -1};
}