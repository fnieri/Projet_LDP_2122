#include "cell.h"
#include "common.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>
#include <utility>

Cell::Cell(Point center, int cellSize, Candy candy) : center{center}, cellSize{cellSize},
                                                      candyPtr{make_unique<Candy>(candy)} {}

Cell::Cell(const Cell &c) {
    center = c.center;
    cellSize = c.cellSize;
    candyPtr = make_unique<Candy>(*c.candyPtr);
}

void Cell::draw() {
    candyPtr->draw(center.x - cellSize / 2, center.y - cellSize / 2, candyPtr->w(), candyPtr->h());
}

bool Cell::contains(Point p) {
    return p.x >= center.x - cellSize / 2 &&
           p.x < center.x + cellSize / 2 &&
           p.y >= center.y - cellSize / 2 &&
           p.y < center.y + cellSize / 2;
}

Color Cell::getColor() {
    return candyPtr->getColor();
}

void Cell::setCandy(const Candy& candy) {
    std::cout << "hello im a trouble maker" << std::endl;
    // change value of candyPtr
    unique_ptr<Candy> ca = make_unique<Candy>(candy);
    candyPtr = std::move(ca);
    std::cout << "setCandy: " << to_string(static_cast<double>(candyPtr->getColor())) << std::endl;
}


