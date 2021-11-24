#include "candy.h"

Candy::Candy(const char *filename, Point center, Color color) : 
    Fl_PNG_Image(filename), center(center), filename(filename), color{color} {
        std::cout << this->filename;
        std::cout << this->fail();

    }

Candy::Candy(const Candy &c) : 
    Fl_PNG_Image{c.filename}, center{c.center}, filename(c.filename) {
        std::cout << this->filename;
        std::cout << this->fail();

    }

Candy::~Candy()=default;
//Candy::Candy(const char *filename, Point center, Fl_Color color) : 
  //  Fl_PNG_Image{filename}, center{center}, filename{filename}, color{color} {}

Color Candy::getColor() const {
    return this->color;
}

Point Candy::getCenter(){
    return this->center;
}

void Candy::setColor(Color newColor) {
    this->color = newColor;
}
void Candy::setCenter(Point newCenter) {
    this->center = newCenter;
} 

