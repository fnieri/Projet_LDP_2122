#ifndef __WALLFACTORY_H
#define __WALLFACTORY_H


#include "Common.h"
#include <cstring>
#include "Wall.h"


class WallFactory {
    public:
        static Wall generateWall();
};
#endif