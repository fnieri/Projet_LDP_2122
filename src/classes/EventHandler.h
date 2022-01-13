/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: EventHandler.h
* Date: 13/01/2022
*/

#ifndef __EVENTHANDLER_H
#define __EVENTHANDLER_H

#include "Common.h"
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
