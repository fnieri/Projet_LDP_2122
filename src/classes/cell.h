#ifndef CELL_H
#define CELL_H

#include <Fl/Fl.H>
#include "common.h"
#include "candy.h"
#include <memory>
#include <Fl/Fl_Box.H>
using namespace std;

class Cell {
    Point center;
    int cellSize;
    Fl_Color color;
    Candy candy;
public:
    Cell(Point, int, Fl_Color, Candy);
    bool contains(Point p);
    void draw();
};

#endif
