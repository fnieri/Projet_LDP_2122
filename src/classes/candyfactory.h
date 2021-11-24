#ifndef __CANDYFACTORY_H
#define __CANDYFACTORY_H

#include "common.h"
#include "color.h"
#include <string>
#include "candy.h"


class CandyGenerator {
    Point center;
    Color color;
    public:
        CandyGenerator(Point center);
        Point getCenter();
        Color generateColor();
        std::string generateImageName(Color color);
        Candy generateCandy();

};

#endif