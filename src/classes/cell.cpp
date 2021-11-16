#include "cell.h"
#include "common.h"
#include <FL/fl_draw.H>

Cell::Cell(Point center, int cellSize, Fl_Color color) : center{center}, cellSize(cellSize), color(color) {}

void Cell::draw() const {
    fl_color(color);
    fl_rectf(center.x - cellSize / 2, center.y - cellSize/ 2, cellSize, cellSize);
    fl_color(FL_BLACK);
    fl_rect(center.x - cellSize / 2, center.y - cellSize/ 2, cellSize, cellSize);
}



