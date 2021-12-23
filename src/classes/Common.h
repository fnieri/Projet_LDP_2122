//
// Created by louis on 11/15/21.
//

#ifndef __COMMON_H
#define __COMMON_H
#include <iostream>
#include <experimental/filesystem>


struct Point {
    int x, y;

    bool operator ==(const Point&p) const{
        return (x == p.x && y == p.y);
    }

    bool operator !=(const Point&p) const{
        return (x != p.x || y != p.y);
    }
};

#define NUMBER_OF_COLORS 6
#define WORKING_DIRECTORY std::string(std::experimental::filesystem::current_path())


#endif
