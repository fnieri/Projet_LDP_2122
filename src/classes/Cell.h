#ifndef CELL_H
#define CELL_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>
#include <utility>

#include "Common.h"
#include "Candy.h"
#include "Color.h"

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

    bool isEmpty();
};

#endif