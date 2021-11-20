#include "candy.h"


Candy::Candy () {
    this->generateColor();
    this->setImages();
}


Candy::~Candy() = default;


Color Candy::getColor() {
    return this->color;
}


void Candy::generateColor(){
    srand(time(0));
    this->setColor(static_cast<Color>(rand() % NUMBER_OF_COLORS));
}


void Candy::setColor(Color color){
    this->color = color;
}


void Candy::setImages(){
    std::string candyImagePrefix = generateCandyImagePrefix(this->color);
    this->setIdleImage(candyImagePrefix);
    this->setOnHoverImage(candyImagePrefix);
}


std::string Candy::generateCandyImagePrefix(Color color) {
    std::string returnPrefix;
    switch (color)
    {
    
        case Color::RED:
            returnPrefix = "red";
            break;
        case Color::ORANGE:
            returnPrefix = "orange";
            break;
        case Color::YELLOW:
            returnPrefix = "yellow";
            break;
        case Color::GREEN:
            returnPrefix = "blue";
            break;
        case Color::BLUE:
            returnPrefix = "blue";
            break;
        case Color::PURPLE:
            returnPrefix = "purple";
            break;
        default:
            break;
    }

   return returnPrefix;

}


void Candy::setIdleImage(std::string prefix){
    const char* asd = "/sprites/normal_candies/";
    std::string spritesPath = WORKING_DIRECTORY + asd;
    std::string idleImageName = spritesPath + prefix + CANDY_IDLE_IMAGE_EXTENSION;
    this->candyIdleImage = new Fl_PNG_Image(idleImageName.c_str());

}


void Candy::setOnHoverImage(std::string prefix){
    std::string spritesPath = WORKING_DIRECTORY + "/sprites/normal_candies/";
    std::string onHoverImageName = spritesPath + prefix + CANDY_ON_HOVER_IMAGE_EXTENSION;
    this->candyOnHoverImage = new Fl_PNG_Image(onHoverImageName.c_str());

}

void Candy::mouseClick(Point mouseLoc){}
void Candy::mouseMove(Point mouseLoc){}
