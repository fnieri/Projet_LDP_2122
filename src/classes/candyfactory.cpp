#include "candyfactory.h"

CandyGenerator::CandyGenerator(Point center) : center{center} {}

Point CandyGenerator::getCenter() {
    return this->center;
}

Color CandyGenerator::generateColor() {
    srand(time(0));
    static_cast<Color>(rand() % NUMBER_OF_COLORS);
}

