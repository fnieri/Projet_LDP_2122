#ifndef __CANDY_H
#define __CANDY_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include <string>

class Candy{
    private:
        Fl_PNG_Image* candyIdleImage;
        Fl_PNG_Image* candyOnHoverImage;
        std::vector<Candy> neighbors;
        Point center;
    protected:
        Color color;
    public:
        Candy(Point center);
        Candy(Point center, Color color);
        virtual ~Candy();
        Color getColor() const;
        virtual void setColor(Color newColor);
        virtual void setCenter(Point newCenter);
        virtual Point getCenter();
        virtual void setImages();
        virtual std::string generateCandyImagePrefix(Color color);
        virtual void setIdleImage(std::string prefix);
        virtual Fl_PNG_Image* getIdleImage();
        virtual void setOnHoverImage(std::string prefix);
        virtual Fl_PNG_Image* getOnHoverImage();
        virtual void generateColor();
        virtual void mouseClick(Point mouseLoc);
        virtual void mouseMove(Point mouseLoc);
        virtual bool isEqualColor(Candy &otherCandy);
        //void mouseDrag(Point mouseLoc);

    
};
 
#endif
