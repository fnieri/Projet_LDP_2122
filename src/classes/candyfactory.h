#ifndef __CANDYFACTORY_H
#define __CANDYFACTORY_H

#include "common.h"
#include "color.h"
#include <string>
#include "candy.h"
#include "candyspeciality.h"
#include <cstdlib>
#include <ctime>
class CandyFactory {
    std::string tempfilename;
    public:
        void setfile(std::string file);

        CandyFactory();
        ~CandyFactory();
        Color generateColor();
        std::string generateSpecialityPath(CandySpeciality speciality);
        std::string generateColorPrefix(Color color);
        std::string generateFullPath(CandySpeciality speciality, std::string colorPrefix, std::string specialityPath);
        const char* generateImageName(Color color, CandySpeciality speciality);
//        const char* generateImageName(Color color, Point center, CandySpeciality speciality);
        Candy generateCandy(Point center, CandySpeciality speciality);
        Candy generateCandy(Point center, CandySpeciality speciality, Color color);

};

#endif