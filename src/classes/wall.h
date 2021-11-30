#ifndef __WALL_H
#define __WALL_H

#include <FL/Fl_PNG_Image.H>
#include "common.hpp"

class Wall : public Fl_PNG_Image {
    private:
        Point center;
    public:
        Point getCenter();

};

#endif