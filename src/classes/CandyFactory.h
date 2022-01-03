#ifndef __CANDYFACTORY_H
#define __CANDYFACTORY_H

#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <utility>

#include "Candy.h"
#include "Enums/CandySpeciality.h"
#include "Common.h"
#include "Enums/Color.h"

class CandyFactory {
private:


    static std::string generateSpecialityPath(CandySpeciality speciality);


    static std::string
    generateFullPath(CandySpeciality speciality, const std::string &colorPrefix, const std::string &specialityPath);

    static std::string generateImageName(Color color, CandySpeciality speciality);
    
public:
    static Color generateColor();

    static std::string generateColorPrefix(Color color);

    static Candy generateCandy( CandySpeciality speciality);

    static Candy generateCandy(CandySpeciality speciality, Color color);

    static Candy generateEmptyCandy();
};



#endif