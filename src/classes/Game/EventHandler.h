//
// Created by louis on 19/12/2021.
//

#ifndef TEMP_CLASSES_EVENTHANDLER_H
#define TEMP_CLASSES_EVENTHANDLER_H

#include "../Sources/Common.h"
#include "Game.h"


class EventHandler : virtual public Game {
private:
    Point firstPosition{};
public:
    void resetEvent();
    void setFirstPosition(Point p);
    void handleMouseDrag(Point p);

    void handleMouseEvent(Point p);

};


#endif //TEMP_CLASSES_EVENTHANDLER_H
