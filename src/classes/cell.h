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
    int cellSize, margin;
    unique_ptr<Candy> candyPtr;
    bool drawBox = false;
public:
    Cell(Point, int, const Candy& candy, int margin);

    Cell(const Cell &);

    bool contains(Point p) const;

    void draw();

    Color getColor();

    CandySpeciality getSpeciality();

    void setCandy(const Candy&);

    Candy getCandy();

    void animateCandy(Cell*);

    Point getCenter();

    void setCenter(Point);

    void setHighlighted(bool val);
};

#endif
