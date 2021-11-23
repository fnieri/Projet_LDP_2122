#include "candy.h"

Candy::Candy(const char *filename, Point center) : 
    Fl_PNG_Image(filename), center(center), filename(filename) {}

Candy::Candy(const Candy &c) : 
    Fl_PNG_Image{c.filename}, center{c.center}, filename(c.filename) {}


Candy::Candy(const char *filename, Point center, Fl_Color color) : 
    Fl_PNG_Image{filename}, center{center}, filename{filename}, color{color} {}

Color Candy::getColor() const {
    return this->color;
}

Point Candy::getCenter(){
    return this->center;
}

void Candy::setColor(Color newColor) {

}
void Candy::setCenter(Point newCenter) {
    this->center = newCenter;
} 

