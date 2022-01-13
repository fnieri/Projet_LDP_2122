/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: Wall.cpp
* Date: 13/01/2022
*/
        
#include "Wall.h"

Wall::Wall(const char* filename) :
    Clickable{filename}, filename{filename} {}

Wall::Wall(const Wall &w) : Clickable{w.filename}, filename{w.filename} {}

bool Wall::isEmpty() const  {
    return false;
}