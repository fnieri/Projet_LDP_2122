#ifndef __CANDY_H
#define __CANDY_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include <string>

class Candy : public Fl_PNG_Image {
        Point center;
        const char *filename;
        Color color;
    public:
        //Candy(const char *filename, Point center);
        Candy(const char *filename, Point center);
        Candy(const char *filename, Point center, Fl_Color color);
        Candy(const Candy &c);
        virtual ~Candy();
        Color getColor() const;
        virtual Point getCenter();
        virtual void setColor(Color newColor);
        virtual void setCenter(Point newCenter);
      /*
        virtual void mouseClick(Point mouseLoc);
        virtual void mouseMove(Point mouseLoc);
        virtual bool isEqualColor(Candy &otherCandy);
      */    
};
 
#endif
