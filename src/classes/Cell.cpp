#include "Cell.h"

Cell::Cell(Point center, int cellSize, const Candy &candy, int margin) : center{center}, cellSize{cellSize},
                                                                         margin{margin},
                                                                         candyPtr{make_unique<Candy>(candy)} {
}

Cell::Cell(const Cell &c) {
    center = c.center;
    cellSize = c.cellSize;
    margin = c.margin;
    candyPtr = make_unique<Candy>(*c.candyPtr);
}

void Cell::draw() {
    if (drawBox) {
        array<Point, 5> points{
                Point{center.x - cellSize / 10, center.y - cellSize / 4},
                Point{center.x - cellSize / 10, center.y + cellSize},
                Point{center.x + cellSize, center.y + cellSize},
                Point{center.x + cellSize, center.y - cellSize},
                Point{center.x + cellSize, center.y - cellSize / 4}};
        fl_color(FL_LIGHT3);
        fl_begin_polygon();
        for (auto &point: points) {
            fl_vertex(point.x, point.y);
        }
        fl_end_polygon();
    }
    candyPtr->draw(center.x - cellSize / 2, center.y - cellSize / 2, candyPtr->w(), candyPtr->h());
}

void Cell::setHighlighted(bool val) {
    drawBox = val;
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
    }
}

bool Cell::contains(Point p) const {
    return p.x >= center.x  - cellSize / 4 &&
           p.x < center.x + cellSize &&
           p.y >= center.y - cellSize / 4 &&
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

CandySpeciality Cell::getSpeciality() {
    return candyPtr->getSpeciality();
}
