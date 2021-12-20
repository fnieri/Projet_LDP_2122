#include "EventHandler.h"

EventHandler::EventHandler() : {}


void EventHandler::reset() {
    firstPosition = Point{-1, -1};
    secondPosition = Point{-1, -1};
}

Point EventHandler::getFirstPosition() {
    return firstPosition;
}

Point EventHandler::getSecondPosition() {
    return secondPosition;
}

void EventHandler::setFirstPosition(Point p) {
    firstPosition = getPositionOfCell(p);
}

void EventHandler::setSecondPosition(Point p) {
    secondPosition = getPositionOfCell(p);
}

void EventHandler::setSelectedCell(Point p) {
    setFirstPosition(p);
    setSelectedCell(cellAt(p));
    setSelectedCellPosition(p);
}


void EventHandler::setSwapCell(Point p) {
    setSwapCell(cellAt(p));
    setSwapCellPosition(p);
}

void EventHandler::handleMouseEvent(Point p) {

    if (p.x < 0 || p.y < 0) return;

    if (firstPosition == Point{-1, -1}) {
        setSelectedCell(p);
    } else {
        setSecondPosition(p);
        if (getSecondPosition() != getFirstPosition()) {

            setAcceptInput(false);
            swapCells(cellAt(p), secondPosition);
            reset(); //Pls don't hurt me it's to recognise board reset and this reset

        } else {
            setFirstPosition(p);
        }
    }
}