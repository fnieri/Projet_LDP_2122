//
// Created by louis on 19/12/2021.
//

#ifndef TEMP_CLASSES_EVENTHANDLER_H
#define TEMP_CLASSES_EVENTHANDLER_H

#include "Common.h"
#include "Game.h"


class EventHandler : virtual public Game {
private:
    Point firstPosition{};
//    Point secondPosition{-1 , -1};
public:
    void resetEvent();
//    Point getFirstPosition();
//    Point getSecondPosition();
    void setFirstPosition(Point p);

//    void setSecondPosition(Point p);
//    void setEventSelectedCell(Point p);
//    void setEventSwapCell(Point p);
    void handleMouseDrag(Point p);

    void handleMouseEvent(Point p);

};


#endif //TEMP_CLASSES_EVENTHANDLER_H
