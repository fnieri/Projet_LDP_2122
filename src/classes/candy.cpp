#include <candy.hpp>

Candy::Candy (Color color) : color{color} {};

Candy::~Candy() = default;

Color Candy::getColor() {
    return this->color;
}

void Candy::setColor(Color color){
    this->color = color;
}

void Candy::setImages(){
    Color randomColor = static_cast<Color>(rand() % NUMBER_OF_COLORS);
    std::string candyImagePrefix = generateCandyImagePrefix(randomColor);
    
    this->setColor(randomColor);
    this->setIdleImage(candyImagePrefix);
    this->setOnHoverImage(candyImagePrefix);
}

std::string Candy::generateCandyImagePrefix(Color color) {
    std::string returnPrefix;
    switch (color)
    {
    
        case Color::RED:
            returnPrefix == "red";
            break;
        case Color::ORANGE:
            returnPrefix == "orange";
            break;
        case Color::YELLOW:
            returnPrefix == "yellow";
            break;
        case Color::GREEN:
            returnPrefix == "blue";
            break;
        case Color::BLUE:
            returnPrefix == "blue";
            break;
        case Color::PURPLE:
            returnPrefix == "purple";
            break;
        default:
            break;
    }

   return returnPrefix;

}
/*
void Candy::setIdleImage(std::string prefix){
    std::string idleImageName = prefix + CANDY_IDLE_IMAGE_EXTENSION;
    this->candyIdleImage = new Fl_PNG_Image(WORKING_PATH);

}
*/