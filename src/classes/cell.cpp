#include "cell.h"
#include "common.h"
#include <FL/fl_draw.H>

/*Cell::Cell(Point center, int cellSize, Fl_Color color, shared_ptr<Candy> candy) : center{center}, cellSize(cellSize), color(color), candy{candy} 
{
    Fl_Box *ret = new Fl_Box(center, cellSize, cellSize, "carmine");

}
*/

Cell::Cell(Point center, int cellSize, Fl_Color color, shared_ptr<Candy> candy) :
    Fl_Box{center.x, center.y, cellSize, cellSize, "cell"} {
        this->image(candy->getIdleImage());
        this->show();
        this->redraw();
}


Cell::Cell(const Cell& cell) : Fl_Box{cell.x(), cell.y(), cell.w(), cell.h(), "cell"} {
    this->box(FL_UP_BOX);
    this->image(cell.candy->getIdleImage());
  //  this->show();
  //  this->redraw();
}
Cell::~Cell() {};

void Cell::draw() const {
    fl_color(color);
    fl_rectf(center.x - cellSize / 2, center.y - cellSize/ 2, cellSize, cellSize);
    fl_color(FL_BLACK);
    fl_rect(center.x - cellSize / 2, center.y - cellSize/ 2, cellSize, cellSize);

}

bool Cell::contains(Point p) {
    return p.x >= center.x - cellSize / 2 &&
           p.x < center.x + cellSize / 2 &&
           p.y >= center.y - cellSize / 2 &&
           p.y < center.y + cellSize / 2;
}

void Cell::setColor(Fl_Color color) {
    this->color = color;
}

shared_ptr<Candy> Cell::getCandy() {
    return candy;
}
