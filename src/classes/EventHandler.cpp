//
// Created by louis on 19/12/2021.
//

#include "EventHandler.h"

void EventHandler::resetEvent() {
    firstPosition = Point{};
}

void EventHandler::setFirstPosition(Point p) {
    firstPosition = getPositionOfCell(p);
}

void EventHandler::handleMouseDrag(Point p){
    Fl::unlock();
    if (p.x < 0 || p.y < 0) return;
    if (firstPosition == Point{}) {
        setFirstPosition(p);
    }
    else {
        Point secondPosition = getPositionOfCell(p);
        if (firstPosition != secondPosition) {
            handleBoardDrag(firstPosition, secondPosition);
            resetEvent();
        }
        else {
            setFirstPosition(p);
        }
    }
}

void EventHandler::handleMouseEvent(Point p) {
    if (p.x < 0 || p.y < 0) return;
    handleBoardContains(p);
}