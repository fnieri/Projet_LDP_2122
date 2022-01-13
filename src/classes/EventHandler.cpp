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
    //First move or first move after successful swap
    if (firstPosition == Point{}) {
        setFirstPosition(p);
    }
    else {
        //After first move
        Point secondPosition = getPositionOfCell(p);
        //As Fl_DRAG updates at every pixel, check everytime if mouse is in another cell
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