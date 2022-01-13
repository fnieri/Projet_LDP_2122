/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: Common.h
* Date: 13/01/2022
*/


#ifndef __COMMON_H
#define __COMMON_H
#include <iostream>
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;


using std::shared_ptr; using std::make_shared;
using std::unique_ptr; using std::make_unique;
using std::dynamic_pointer_cast;
using std::vector;
using std::out_of_range;
using std::array;
using std::to_string;

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
