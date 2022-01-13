/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: CandyFactory.cpp
* Date: 13/01/2022
*/
        
#include "CandyFactory.h"

Color CandyFactory::generateColor() {
    
    return static_cast<Color>(rand() % NUMBER_OF_COLORS);;
}


std::string CandyFactory::generateSpecialityPath(CandySpeciality speciality) {
    if (speciality != CandySpeciality::NONE) return "/sprites/special_candies/";
    return "/sprites/normal_candies/";
}


std::string CandyFactory::generateColorPrefix(Color color) {
    switch (color) {
        case Color::RED: return "red";
        case Color::ORANGE: return "orange";
        case Color::YELLOW: return "yellow";
        case Color::GREEN: return "green";
        case Color::BLUE: return "blue";
        case Color::PURPLE: return "purple";
        case Color::NONE: return " ";
        default:
            break;
    }
    return "";
}

std::string
CandyFactory::generateFullPath(CandySpeciality speciality, const std::string &colorPrefix,
                               const std::string &specialityPath) {
    std::string candyPath;
    switch (speciality) {
        case CandySpeciality::NONE:
            candyPath = "_01.png";
            break;
        case CandySpeciality::STRIPED_HORIZONTAL:
            candyPath = "_horizontal.png";
            break;
        case CandySpeciality::STRIPED_VERTICAL:
            candyPath = "_vertical.png";
            break;
        case CandySpeciality::BOMB:
            candyPath = "_bomb.png";
            break;
        case CandySpeciality::MULTICOLOR:
            return specialityPath + "multicolor.png";
        default:
            break;
    }
    return specialityPath + colorPrefix + candyPath;
}

std::string CandyFactory::generateImageName(Color color, CandySpeciality speciality) {
    std::string colorPrefix = generateColorPrefix(color);
    std::string specialityPath = generateSpecialityPath(speciality);
    std::string fullPath = generateFullPath(speciality, colorPrefix, specialityPath);

    return fullPath;
}

Candy CandyFactory::generateCandy(CandySpeciality speciality) {
    Color color;
    if (speciality == CandySpeciality::MULTICOLOR)
        color = Color::MULTICOLOR;
    else
        color = CandyFactory::generateColor();
    std::string filename = WORKING_DIRECTORY + CandyFactory::generateImageName(color, speciality);
    char *fullPathChar = new char[filename.length() + 1];
    strcpy(fullPathChar, filename.c_str());
    return {fullPathChar, color, speciality};
}

Candy CandyFactory::generateCandy(CandySpeciality speciality, Color color) {
    std::string filename = WORKING_DIRECTORY + CandyFactory::generateImageName(color, speciality);
    char *fullPathChar = new char[filename.length() + 1];
    strcpy(fullPathChar, filename.c_str());
    return {fullPathChar, color, speciality};
}

Candy CandyFactory::generateEmptyCandy() {
    return {nullptr, Color::NONE};
}
Candy CandyFactory::generateBoomCandy() {
    std::string filename = WORKING_DIRECTORY + "/sprites/normal_candies/explosion.png";
    char *fullPathChar = new char[filename.length() + 1];
    strcpy(fullPathChar, filename.c_str());
    return {fullPathChar, Color::NONE};
}