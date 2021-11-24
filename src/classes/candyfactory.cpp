#include "candyfactory.h"

CandyFactory::CandyFactory() {}
CandyFactory::~CandyFactory()=default;

Color CandyFactory::generateColor() {
    Color randomColor;
    std::srand(time(NULL));
    std::cout << rand();
    randomColor = static_cast<Color>(std::rand() % NUMBER_OF_COLORS);
    return randomColor;
}


std::string CandyFactory::generateSpecialityPath(CandySpeciality speciality) {
    std::string specialityPath;

    if (speciality != CandySpeciality::NONE) {
        specialityPath = "/sprites/special_candies/";
    }
    else {
        specialityPath = "/sprites/normal_candies/";
    }
    return specialityPath;
}


std::string CandyFactory::generateColorPrefix(Color color) {
    std::string colorPrefix;
      switch (color) {
    
        case Color::RED:
            colorPrefix = "red_";
            break;
        case Color::ORANGE:
            colorPrefix = "orange_";
            break;
        case Color::YELLOW:
            colorPrefix = "yellow_";
            break;
        case Color::GREEN:
            colorPrefix = "green_";
            break;
        case Color::BLUE:
            colorPrefix = "blue_";
            break;
        case Color::PURPLE:
            colorPrefix = "purple_";
            break;
        default:
            break;

    }
    return colorPrefix;
}

std::string CandyFactory::generateFullPath(CandySpeciality speciality, std::string colorPrefix, std::string specialityPath) {
    std::string candyPath;
  
    switch (speciality) {
        case CandySpeciality::NONE:
            candyPath = "01.png";
            break;
        case CandySpeciality::STRIPED_HORIZONTAL:
            candyPath = "horizontal.png";
            break;
        case CandySpeciality::STRIPED_VERTICAL:
            candyPath = "vertical.png";
            break;
        case CandySpeciality::BOMB:
            candyPath = "bomb.png";
            break;
        case CandySpeciality::MULTICOLOR:
            candyPath = "multicolor.png";
            break;
        default:
            break;
    }
    std::string fullPath = WORKING_DIRECTORY + specialityPath + colorPrefix + candyPath;
   // std::cout << fullPath.c_str();
   std::cout << "This is genfullPath filename: " << fullPath << "\n";
    this->setfile(fullPath);
    return fullPath;
}

void CandyFactory::setfile(std::string file) {
    this->tempfilename = file;
}

const char* CandyFactory::generateImageName(Color color, CandySpeciality speciality) {
    std::string colorPrefix = this->generateColorPrefix(color);
    std::string specialityPath = this->generateSpecialityPath(speciality);
    const char* fullPath = this->generateFullPath(speciality, colorPrefix, specialityPath).c_str();
    std::cout << "This is genImage filename: " << fullPath << "\n";
    return fullPath;
}

Candy CandyFactory::generateCandy(Point center, CandySpeciality speciality) {
    Color color = this->generateColor();
    std::cout << "entered 1 with color:" << static_cast<int>(color) << "and speciality" << speciality << "\n";
    const char *filename = this->generateImageName(color, speciality);
    return Candy(tempfilename.c_str(), center, color);
}

Candy CandyFactory::generateCandy(Point center, CandySpeciality speciality, Color color) {
    const char *filename = this->generateImageName(color, speciality);
    return Candy(tempfilename.c_str(), center, color);

}