/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: Cell.cpp
* Date: 13/01/2022
*/
        
#include "Cell.h"

Cell::Cell(Point center, int cellSize, Clickable *cellObject, int margin) : center{center}, cellSize{cellSize},
                                                                         margin{margin} {
    
    castClickable(cellObject); //Cast from base class to derived class
    setClickable(*cellObject);              
}

Cell::Cell(const Cell &c) {
    center = c.center;
    cellSize = c.cellSize;
    margin = c.margin;
    cellClickable = std::move(c.cellClickable);
}

// https://en.cppreference.com/w/cpp/language/dynamic_cast
void Cell::castClickable(Clickable* cellClickable) {
    if (cellClickable->visitCandy()) 
        cellClickable = dynamic_cast<Candy*>(cellClickable);
    
    else if (cellClickable->visitWall())
       cellClickable = dynamic_cast<Wall*>(cellClickable);

    else if (cellClickable->visitIcing())
        cellClickable = dynamic_cast<Icing*>(cellClickable);
    
} 

void Cell::castClickable(shared_ptr<Clickable> cellClickable) {
    if (cellClickable->visitCandy())
        cellClickable = dynamic_pointer_cast<Candy>(cellClickable);

    else if (cellClickable->visitWall())
        cellClickable = dynamic_pointer_cast<Wall>(cellClickable);

    else if (cellClickable->visitIcing()) 
        cellClickable = dynamic_pointer_cast<Icing>(cellClickable);
    
}

template <class cellObject>
shared_ptr<cellObject> Cell::returnCasted(){
    return dynamic_pointer_cast<cellObject>(cellClickable);
}

bool Cell::isEmpty() {
    return cellClickable->isEmpty();
}

void Cell::draw() {
    //Draw a box beneath candy with color
    //FL_LIGHT3 is for hover, FL_RED is for suggestion, none is default
    if (drawBox || suggesting) {
        array<Point, 5> points{
                Point{center.x - cellSize / 10, center.y - cellSize / 4},
                Point{center.x - cellSize / 10, center.y + cellSize},
                Point{center.x + cellSize, center.y + cellSize},
                Point{center.x + cellSize, center.y - cellSize},
                Point{center.x + cellSize, center.y - cellSize / 4}};
        fl_color(highlightColor);
        fl_begin_polygon();
        for (auto &point: points) {
            fl_vertex(point.x, point.y);
        }
        fl_end_polygon();
    }
    cellClickable->draw(center.x - cellSize / 2, center.y - cellSize / 2, cellClickable->w(), cellClickable->h());
}

void Cell::resetHighlight() {
    setHighlightColor(FL_LIGHT3);
    setHighlighted(false);
    setSuggestion(false);
}

void Cell::setSuggestion(bool suggestion) {
    suggesting = suggestion;
}

void Cell::setHighlightColor(Fl_Color color) {
    highlightColor = color;
}

void Cell::setHighlighted(bool val) {
    drawBox = val;
}

void Cell::animateCandy(Cell *swapCell) {
    //Animate two candies swapping cell
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

void Cell::setClickable(const Clickable &clickable) {
    if (auto tmp = dynamic_cast<const Candy*>(&clickable))  {
        cellClickable = make_shared<Candy>(*tmp);
    }
    else if (auto tmp = dynamic_cast<const Wall*>(&clickable))  {
        cellClickable = make_shared<Wall>(*tmp);
    }

    else if (auto tmp = dynamic_cast<const Icing*>(&clickable))  {
        cellClickable = make_shared<Icing>(*tmp);
    }
}


Candy* Cell::getCandy() {
     return dynamic_cast<Candy*>(cellClickable.get());
}

Point Cell::getCenter() {
    return center;
}


void Cell::setCenter(Point newCenter) {
    center.x = newCenter.x;
    center.y = newCenter.y;
}


CandySpeciality Cell::getSpeciality() {
    if (cellClickable->visitCandy()) 
        return dynamic_pointer_cast<Candy>(cellClickable)->getSpeciality();  
    return CandySpeciality::NONE;
}

Color Cell::getColor() {
    if (cellClickable->visitCandy()) 
        return dynamic_pointer_cast<Candy>(cellClickable)->getColor();  
    return Color::NONE;
}

IcingStatus Cell::getStatus() {
    if (cellClickable->visitIcing())
        return dynamic_pointer_cast<Icing>(cellClickable)->getStatus();  
    return IcingStatus::EMPTY; 
}  

bool Cell::hasCandy() {
    return cellClickable->visitCandy();
}

bool Cell::hasIcing() {
    return cellClickable->visitIcing();
}

bool Cell::hasWall() {
    return cellClickable->visitWall();
}