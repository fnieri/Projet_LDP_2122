//
// Created by louis on 11/15/21.
//

#ifndef __COMMON_H
#define __COMMON_H
#include <iostream>
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;

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
#define WORKING_DIRECTORY std::string(fs::current_path())
#define BEST_SCORE_FILE std::string("best_score/best_score.txt")


#endif
