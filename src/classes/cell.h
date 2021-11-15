#ifndef CELL_H
#define CELL_H

#include <Fl/Fl.H>
#include "common.h"

using namespace std;


class Cell {
    Point center;
    int cellSize;
public:
    Cell(Point center, int cellSize);
//    Point getCenter();
//    void setCenter(Point center);

    void draw() const;
};

#endif