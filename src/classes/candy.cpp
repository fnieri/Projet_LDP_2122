#include "candy.h"

Candy::Candy(const char *filename, Color color) :
        Fl_PNG_Image(filename), filename(filename), color{color} {
    // FLTK automatically deletes filename
}

Candy::Candy(const Candy &c) :
        Fl_PNG_Image{c.filename}, filename(c.filename), color{c.color} {}

Candy::~Candy() = default;

Color Candy::getColor() const {
    return color;
}

void Candy::setColor(Color newColor) {
    color = newColor;
}


