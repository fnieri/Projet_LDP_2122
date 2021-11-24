#include "cell.h"
#include "common.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>
#include <utility>

Cell::Cell(Point center, int cellSize, Fl_Color color, Candy candy) : center{center}, cellSize{cellSize}, color{color},
                                                                      candy{candy} {}

void Cell::draw() {
 //   fl_color(color);
   // fl_rectf(center.x - cellSize / 2, center.y - cellSize / 2, cellSize, cellSize);
   // fl_color(FL_BLACK);
   // fl_rect(center.x - cellSize / 2, center.y - cellSize / 2, cellSize, cellSize);
  //  fl_rectf(center.x, center.y, cellSize, cellSize);
  //  fl_color(FL_BLACK);
  //  fl_rect(center.x, center.y, cellSize, cellSize);
    candy.draw(center.x - cellSize / 2, center.y - cellSize / 2, candy.w(), candy.h());
    

}

bool Cell::contains(Point p) {
    return p.x >= center.x - cellSize / 2 &&
           p.x < center.x + cellSize / 2 &&
           p.y >= center.y - cellSize / 2 &&
           p.y < center.y + cellSize / 2;
}
