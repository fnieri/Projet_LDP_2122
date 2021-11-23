#include "cell.h"
#include "common.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>
/*Cell::Cell(Point center, int cellSize, Fl_Color color, shared_ptr<Candy> candy) : center{center}, cellSize(cellSize), color(color), candy{candy} 
{
    Fl_Box *ret = new Fl_Box(center, cellSize, cellSize, "carmine");

}
*/

Cell::Cell(Point center, int cellSize, Fl_Color color, shared_ptr<Candy> candy) :
    Fl_Box {center.x, center.y, cellSize, cellSize, "cell"} {
        this->align(FL_ALIGN_TOP | FL_ALIGN_INSIDE);
     //   cout << candy->getIdleImage();
        
      //  Fl_PNG_Image* candyIdleImage = candy->getIdleImage();
       // std::cout << candyIdleImage->fail() << "bo \n";
       // this->image(candyIdleImage);
        
    //    redraw();
}


Cell::Cell(const Cell& cell) : Fl_Box{cell.x(), cell.y(), cell.w(), cell.h(), "cell"} {
        this->align(FL_ALIGN_TOP | FL_ALIGN_INSIDE);
        
 //   if (cell.candy->getIdleImage()->w() > this->w() || cell.candy->getIdleImage()->h() > this->h()) {
 //       Fl_Image *temp;
 //   if (cell.candy->getIdleImage()->w() > cell.candy->getIdleImage()->h()) {
 //       temp = cell.candy->getIdleImage()->copy(this->w(), cell.candy->getIdleImage()->h() * cell.candy->getIdleImage()->h() / cell.candy->getIdleImage()->w());
 //   } else {
 //       temp = cell.candy->getIdleImage()->copy(this->w() * cell.candy->getIdleImage()->w() / cell.candy->getIdleImage()->h(), this->h());
 //   }
 //   cell.candy->getIdleImage() = (Fl_PNG_Image *) temp;
        
    //    this->redraw();
}
Cell::~Cell() {};

void Cell::draw()  {
    fl_color(color);
    fl_rectf(center.x - cellSize / 2, center.y - cellSize/ 2, cellSize, cellSize);
    fl_color(FL_BLACK);
    fl_rect(center.x - cellSize / 2, center.y - cellSize/ 2, cellSize, cellSize);
        
     //   Fl_PNG_Image* candyIdleImage = this->candy->getIdleImage();
     //   std::cout << candyIdleImage->fail() << "bo \n";
     //   this->image(candyIdleImage);
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
    return this->candy;
}
