#include "Candy.h"

Candy::Candy(const char *filename, Color color, CandySpeciality speciality) :
        Clickable(filename), filename(filename), color{color}, speciality{speciality} {}

Candy::Candy(const Candy &c) :
        Clickable{c.filename}, filename(c.filename), color{c.color}, speciality{c.speciality} {}

Candy::~Candy() = default;

Color Candy::getColor() const {
    return color;
}

CandySpeciality Candy::getSpeciality() const {
    return speciality;
}
