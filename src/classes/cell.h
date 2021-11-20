#ifndef CELL_H
#define CELL_H

#include <Fl/Fl.H>
#include "common.h"

using namespace std;


class Cell {
    Point center;
    int cellSize;
    Fl_Color color;
public:
    Cell(Point, int, Fl_Color);
    bool contains(Point p);
    void draw() const;
    void setColor(Fl_Color color);
};

#endif
