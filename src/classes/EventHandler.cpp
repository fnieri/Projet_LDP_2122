//
// Created by louis on 19/12/2021.
//

#include "EventHandler.h"
//
//void EventHandler::eventReset() {
//    firstPosition = Point{-1, -1};
//    secondPosition = Point{-1, -1};
//}
//
//Point EventHandler::getFirstPosition() {
//    return firstPosition;
//}
//
//Point EventHandler::getSecondPosition() {
//    return secondPosition;
//}
//
//void EventHandler::setFirstPosition(Point p) {
//    firstPosition = getPositionOfCell(p);
//}
//
//void EventHandler::setSecondPosition(Point p) {
//    secondPosition = getPositionOfCell(p);
//}
//
//void EventHandler::setSelectedCell(Cell *newCell) {
//    selectedCell = newCell;
//}
//
//void EventHandler::setEventSelectedCell(Point p) {
//    setFirstPosition(p);
//    setSelectedCell(cellAt(p));
////    setSelectedCellPosition(p);
//}
//
//
//void EventHandler::setEventSwapCell(Point p) {
//    setSwapCell(cellAt(p));
//    setSwapCellPosition(p);
//}

void EventHandler::handleMouseEvent(Point p) {
    if (p.x < 0 || p.y < 0) return;
    handleBoardContains(p);



//    if (firstPosition == Point{-1, -1}) {
//        setEventSelectedCell(p);
//    } else {
//        setSecondPosition(p);
//        if (getSecondPosition() != getFirstPosition()) {
////            setAcceptInput(false);
//            swapCells(cellAt(p), secondPosition);
//            eventReset();
//        } else {
//            setFirstPosition(p);
//        }
//    }
}