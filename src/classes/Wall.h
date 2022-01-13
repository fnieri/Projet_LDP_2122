/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: Wall.h
* Date: 13/01/2022
*/

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
        bool isEmpty() const override;
        bool visitCandy() override {return false;};
        bool visitIcing() override {return false;};
        bool visitWall() override {return true;};

};

#endif