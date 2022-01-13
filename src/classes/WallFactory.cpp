/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: WallFactory.cpp
* Date: 13/01/2022
*/
        
#include "WallFactory.h"

Wall WallFactory::generateWall() {
    std::string filename = WORKING_DIRECTORY + "/sprites/wall/wall.png";
    char *fullPathChar = new char[filename.length() + 1];
    strcpy(fullPathChar, filename.c_str());
    return {fullPathChar};
}