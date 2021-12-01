#include "cell.h"
#include "common.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>
#include <utility>

Cell::Cell(Point center, int cellSize, const Candy &candy) : center{center}, cellSize{cellSize},
                                                             candyPtr{make_unique<Candy>(candy)} {
}

Cell::Cell(const Cell &c) {
    center = c.center;
    cellSize = c.cellSize;
    candyPtr = make_unique<Candy>(*c.candyPtr);
}

void Cell::draw() {
    candyPtr->draw(center.x - cellSize / 2, center.y - cellSize / 2, candyPtr->w(), candyPtr->h());
}

void Cell::animateCandy(Cell *swapCell) {
    Point destination = swapCell->getCenter();
    while (center.x != destination.x || center.y != destination.y) {
        Point swapCenter = swapCell->getCenter();
        if (center.x != destination.x) {
            if (center.x < destination.x) {
                center.x += 1;
                swapCell->setCenter(Point{swapCenter.x - 1, swapCenter.y});
            } else {
                center.x -= 1;
                swapCell->setCenter(Point{swapCenter.x + 1, swapCenter.y});
            }
        } else if (center.y != destination.y) {
            if (center.y < destination.y) {
                center.y += 1;
                swapCell->setCenter(Point{swapCenter.x, swapCenter.y - 1});
            } else {
                center.y -= 1;
                swapCell->setCenter(Point{swapCenter.x, swapCenter.y + 1});
            }
        } else break;
        Fl::wait(0.005);
//        Fl::redraw(); idk if u need this but i don't
    }
}

void Cell::handleMove() {
}

void Cell::showNormal() {
}

void Cell::animateGravity(Point destination) {
    if (destination.x == center.x) { // little verification so we don't accidentally break everything lol
        while (center.y != destination.y) {
            center.y += 1;
            Fl::wait(0.003);
        }
    }
}

bool Cell::contains(Point p) {
    return p.x >= center.x - cellSize &&
           p.x < center.x + cellSize &&
           p.y >= center.y - cellSize &&
           p.y < center.y + cellSize;
}

Color Cell::getColor() {
    return candyPtr->getColor();
}

void Cell::setCandy(const Candy &candy) {
    unique_ptr<Candy> ca = make_unique<Candy>(candy);
    candyPtr = std::move(ca);
}

Candy Cell::getCandy() {
    return *candyPtr;
}

Point Cell::getCenter() {
    return center;
}

void Cell::setCenter(Point newCenter) {
    center.x = newCenter.x;
    center.y = newCenter.y;
}


