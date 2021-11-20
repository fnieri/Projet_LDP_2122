#ifndef CELL_H
#define CELL_H

#include <Fl/Fl.H>
#include "common.h"
#include "candy.h"
#include <memory>
#include <Fl/Fl_Box.H>
using namespace std;

class Cell : public Fl_Box {
    Point center;
    int cellSize;
    Fl_Color color;
    shared_ptr<Candy> candy;
public:
    Cell(Point, int, Fl_Color color, shared_ptr<Candy> candy);
    Cell(const Cell&);
    ~Cell();
    bool contains(Point p);
    void draw() const;
    shared_ptr<Candy> getCandy();
    void setColor(Fl_Color color);
};

#endif
