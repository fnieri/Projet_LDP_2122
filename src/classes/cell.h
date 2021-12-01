#ifndef CELL_H
#define CELL_H

#include <Fl/Fl.H>
#include "common.h"
#include "candy.h"
#include <memory>
#include <Fl/Fl_Box.H>
#include "color.h"

using namespace std;

class Cell {
    Point center;
    int cellSize;
    unique_ptr<Candy> candyPtr;
public:
    Cell(Point, int, const Candy& candy);

    Cell(const Cell &);

    bool contains(Point p);

    void draw();

    Color getColor();

    void setCandy(const Candy&);

    Candy getCandy();

    void animateCandy(Cell*);

    Point getCenter();

    void setCenter(Point);

    void animateGravity(Point destination);
};

#endif
