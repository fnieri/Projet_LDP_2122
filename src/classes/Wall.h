#ifndef __WALL_H
#define __WALL_H

#include <FL/Fl_PNG_Image.H>
#include "Common.h"
#include "Clickable.h"

class Wall : public Clickable {
    private:
        const char* filename;
    public:
        ~Wall()=default;
        Wall(const char* filename);
        Wall(const Wall &w);
};

#endif