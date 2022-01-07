#ifndef __WALL_H
#define __WALL_H

#include <FL/Fl_PNG_Image.H>
#include "../Sources/Common.h"
#include "Clickable.h"

class Wall : public Clickable {
    private:
        const char* filename;
    public:
        ~Wall()=default;
        Wall(const char* filename);
        Wall(const Wall &w);
        bool isEmpty() const override;
        bool visitCandy() override {return false;};
        bool visitIcing() override {return false;};
        bool visitWall() override {return true;};

};

#endif