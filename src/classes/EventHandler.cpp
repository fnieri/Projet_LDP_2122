/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: EventHandler.cpp
* Date: 13/01/2022
*/
        
#include "EventHandler.h"

void EventHandler::resetEvent() {
    firstPosition = Point{};
}

void EventHandler::setFirstPosition(Point p) {
    firstPosition = getPositionOfCell(p);
}

void EventHandler::handleMouseDrag(Point p){
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