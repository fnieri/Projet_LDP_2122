#include "Candy.h"


Candy::Candy(const char *filename, Color color, CandySpeciality speciality) :
        Fl_PNG_Image(filename), filename(filename), color{color}, speciality{speciality} {}

Candy::Candy(const Candy &c) :
        Fl_PNG_Image{c.filename}, filename(c.filename), color{c.color}, speciality{c.speciality} {}

Candy::~Candy() = default;

Color Candy::getColor() const {
    return color;
}

void Candy::setColor(Color newColor) {
    color = newColor;
}

CandySpeciality Candy::getSpeciality() const {
    return speciality;
}
