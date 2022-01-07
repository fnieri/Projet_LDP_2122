#ifndef __WALLFACTORY_H
#define __WALLFACTORY_H


#include "../Sources/Common.h"
#include <cstring>
#include "../Clickables/Wall.h"


class WallFactory {
    public:
        static Wall generateWall();
};
#endif