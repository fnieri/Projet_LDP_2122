#include "candy.h"

Candy::Candy(const char *filename, Point center, Color color) :
        Fl_PNG_Image(filename), center(center), filename(filename), color{color} {
    // we will need to delete the filename char to avoid memory leak
}

Candy::Candy(const Candy &c) :
        Fl_PNG_Image{c.filename}, center{c.center}, filename(c.filename), color{c.color} {}

Candy::~Candy() = default;

Color Candy::getColor() const {
    return this->color;
}

Point Candy::getCenter() {
    return this->center;
}

void Candy::setColor(Color newColor) {
    this->color = newColor;
}

void Candy::setCenter(Point newCenter) {
    this->center = newCenter;
} 

