#ifndef __CANDY_H
#define __CANDY_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include <string>

class Candy{
    private:
        Fl_PNG_Image *candyIdleImage;
        Fl_PNG_Image *candyOnHoverImage;
        std::vector<Candy> neighbors;
    protected:
        Color color;
    public:
        Candy();
        Candy(Color color);
        ~Candy();
        Color getColor() const;
        virtual void setColor(Color color);
        
        virtual void setImages();
        virtual std::string generateCandyImagePrefix(Color color);
        virtual void setIdleImage(std::string prefix);
        virtual void setOnHoverImage(std::string prefix);
        virtual void generateColor();
        virtual void mouseClick(Point mouseLoc);
        virtual void mouseMove(Point mouseLoc);
        virtual bool isEqualColor(Candy &otherCandy);
        //void mouseDrag(Point mouseLoc);

    
};
 
#endif
