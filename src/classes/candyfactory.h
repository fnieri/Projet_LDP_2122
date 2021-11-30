#ifndef __CANDYFACTORY_H
#define __CANDYFACTORY_H

#include "common.hpp"
#include "color.h"
#include <string>
#include "candy.h"
#include "candyspeciality.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <utility>

class CandyFactory {
public:

    CandyFactory();

    static Color generateColor();

    static std::string generateSpecialityPath(CandySpeciality speciality);

    static std::string generateColorPrefix(Color color);

    static std::string
    generateFullPath(CandySpeciality speciality, const std::string &colorPrefix, const std::string &specialityPath);

    static std::string generateImageName(Color color, CandySpeciality speciality);


    static Candy generateCandy(CandySpeciality speciality);

    static Candy generateCandy(CandySpeciality speciality, Color color);


};

#endif