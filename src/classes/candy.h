#ifndef __CANDY_H
#define __CANDY_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include <string>

class Candy : public Fl_PNG_Image {
        Point center{};
        const char *filename;
    public:
        Candy(const char *filename, Point center);
        Candy(const Candy &c);
};
 
#endif
