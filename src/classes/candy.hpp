#ifndef __CANDY_HPP
#define __CANDY_HPP

#include <Fl_PNG_Image.H>
#include "common.h"
#include <color.hpp>
#include <string>

class Candy{
    private:
        Color color;
        bool isSpecial;
        Fl_PNG_Image candyIdleImage;
        Fl_PNG_Image candyOnHoverImage;
    public:
        Candy(Color color);
        ~Candy();
        Color getColor();
        void setColor(Color color);

        void setImages();
        std::string generateCandyImagePrefix(Color color);
        void setIdleImage(std::string prefix);
        void setOnHoverImage(std::string prefix);

        void mouseClick(Point mouseLoc);
        void mouseMove(Point mouseLoc);
        
        //void mouseDrag(Point mouseLoc);
        // void setSpeciality() 

    
};
 
#endif