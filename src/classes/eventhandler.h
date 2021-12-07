#ifndef __EVENTHANDLER_H
#define __EVENTHANDLER_H

#include<memory>
#include <vector>
#include "board.h"
#include "common.h"

class Board;

class EventHandler{
    private:
        Point firstPosition{-1, -1};
        Point secondPosition{-1, -1};
        Board* board;
    public:
        void reset();
        EventHandler(Board* board);
        Point getFirstPosition();
        Point getSecondPosition();
        void setFirstPosition(Point p);
        void setSecondPosition(Point p);
        void handleDrag(Point p);

        void setSelectedCell(Point p);
        void setSwapCell(Point p);
};

#endif