#ifndef __CANDY_H
#define __CANDY_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include <string>

class Candy{
    private:
        Color color;
        bool isSpecial;
        Fl_PNG_Image *candyIdleImage;
        Fl_PNG_Image *candyOnHoverImage;
    public:
        Candy();
        ~Candy();
        Color getColor();
        void setColor(Color color);

        void setImages();
        std::string generateCandyImagePrefix(Color color);
        void setIdleImage(std::string prefix);
        void setOnHoverImage(std::string prefix);
        void generateColor();
        void mouseClick(Point mouseLoc);
        void mouseMove(Point mouseLoc);
        
        //void mouseDrag(Point mouseLoc);
        // void setSpeciality() 

    
};
 
#endif