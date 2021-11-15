#include "cell.h"
#include "common.h"
#include <FL/fl_draw.H>

Cell::Cell(Point center, int cellSize) : center{center}, cellSize(cellSize) {}

void Cell::draw() const {
    fl_color(FL_WHITE);
    fl_rectf(center.x - Cell::cellSize / 2, center.y - Cell::cellSize/ 2, Cell::cellSize, Cell::cellSize);
    fl_color(FL_BLACK);
    fl_rect(center.x - Cell::cellSize / 2, center.y - Cell::cellSize/ 2, Cell::cellSize, Cell::cellSize);
}



