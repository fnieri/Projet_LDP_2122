#include "Cell.h"

Cell::Cell(Point center, int cellSize, Clickable *cellObject, int margin) : center{center}, cellSize{cellSize},
                                                                         margin{margin} {
    
    castClickable(cellObject); //Cast from base class to derived class
    setObject(*cellObject);              
}

Cell::Cell(const Cell &c) {
    center = c.center;
    cellSize = c.cellSize;
    margin = c.margin;
    cellObjectPtr = std::move(c.cellObjectPtr);
}

// https://en.cppreference.com/w/cpp/language/dynamic_cast
void Cell::castClickable(Clickable* cellClickable) {
    if (isClass<Candy>(cellClickable)) {
        cellClickable = dynamic_cast<Candy*>(cellClickable);
    }

    else if (isClass<Wall>(cellClickable)) {
       cellClickable = dynamic_cast<Wall*>(cellClickable);
    }

    else if (isClass<Icing>(cellClickable)) {
        cellClickable = dynamic_cast<Icing*>(cellClickable);
    }
    
} 

void Cell::castClickable(shared_ptr<Clickable> cellClickable) {
    if (isClass<Candy>(cellClickable)) {
        cellClickable = dynamic_pointer_cast<Candy>(cellClickable);
    }

    else if (isClass<Wall>(cellClickable)) {
        cellClickable = dynamic_pointer_cast<Wall>(cellClickable);
    }

    else if (isClass<Icing>(cellClickable)) {
      
        cellClickable = dynamic_pointer_cast<Icing>(cellClickable);
    }
    
}

template <class objectClass>

shared_ptr<objectClass> Cell::returnCasted(){
    return dynamic_pointer_cast<objectClass>(cellObjectPtr);
}

bool Cell::isEmpty() {
    if (isClass<Candy>())
        return returnCasted<Candy>()->isEmpty();
    else if (isClass<Icing>()) 
        return returnCasted<Icing>()->isEmpty();
    return false;
}

bool Cell::hasObject() {
    if (cellObjectPtr) {
        return true;
    }
    return false;
}

void Cell::draw() {
    if (drawBox) {
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
    cellObjectPtr->draw(center.x - cellSize / 2, center.y - cellSize / 2, cellObjectPtr->w(), cellObjectPtr->h());
}


void Cell::setHighlightColor(Fl_Color color) {
    highlightColor = color;
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



void Cell::setObject(const Clickable &clickable) {
    if (isClass<Candy>(&clickable))  {
        auto tmp = dynamic_cast<const Candy*>(&clickable);  
        cellObjectPtr = make_shared<Candy>(*tmp);
    }
    if (isClass<Wall>(&clickable))  {
        auto tmp = dynamic_cast<const Wall*>(&clickable);  
        cellObjectPtr = make_shared<Wall>(*tmp);
    }

    if (isClass<Icing>(&clickable))  {
        auto tmp = dynamic_cast<const Icing*>(&clickable);  
        cellObjectPtr = make_shared<Icing>(*tmp);
    }
}

template <class objectClass>
bool Cell::isClass(){
    if (auto tmp = dynamic_pointer_cast<objectClass>(cellObjectPtr)) {
        return true;
    }
    return false;
}

template <class objectClass>
bool Cell::isClass(const Clickable* clickable){
    if (auto tmp = dynamic_cast<const objectClass*>(clickable)) {
        return true;
    }
    return false;
}

template <class objectClass>
bool Cell::isClass(Clickable* clickable){
    if (auto tmp = dynamic_cast<objectClass*>(clickable)) {
        return true;
    }
    return false;
}


template <class objectClass>
bool Cell::isClass(shared_ptr<Clickable> clickable) {
    if (auto tmp = dynamic_pointer_cast<objectClass>(clickable)) {
        return true;
    }
    return false;
}


Candy* Cell::getCandy() {
     return dynamic_cast<Candy*>(cellObjectPtr.get());
}


Point Cell::getCenter() {
    return center;
}


void Cell::setCenter(Point newCenter) {
    center.x = newCenter.x;
    center.y = newCenter.y;
}


CandySpeciality Cell::getSpeciality() {
    if (isClass<Candy>()) 
        return dynamic_pointer_cast<Candy>(cellObjectPtr)->getSpeciality();  
}


Color Cell::getColor() {
    if (isClass<Candy>()) 
        return dynamic_pointer_cast<Candy>(cellObjectPtr)->getColor();  
}

IcingStatus Cell::getStatus() {
    if (isClass<Icing>())
        return dynamic_pointer_cast<Icing>(cellObjectPtr)->getStatus();  

}