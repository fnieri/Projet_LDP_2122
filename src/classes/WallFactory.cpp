#include "WallFactory.h"

Wall WallFactory::generateWall() {
    std::string filename = WORKING_DIRECTORY + "/sprites/wall/wall.png";
    char *fullPathChar = new char[filename.length() + 1];
    strcpy(fullPathChar, filename.c_str());
    return {fullPathChar};
}