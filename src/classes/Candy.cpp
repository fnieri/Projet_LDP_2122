/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: Candy.cpp
* Date: 13/01/2022
*/
        
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

bool Candy::isEmpty() const {
    return getColor() == Color::NONE;
}