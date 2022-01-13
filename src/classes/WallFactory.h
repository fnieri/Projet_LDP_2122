/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: WallFactory.h
* Date: 13/01/2022
*/

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