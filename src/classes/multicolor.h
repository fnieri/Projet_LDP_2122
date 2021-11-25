#ifndef __BOMB_H
#define __BOMB_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include <string>
#include "candy.h"

class MultiColor : public Candy {	
    private:
		std::vector<Candy> neighbors;
    	Color color;
    public:
		MultiColor();
		Color getColor();
		void mouseClick(Point mouseLoc);
		void mouseMove(Point mouseLoc);
		void mouseDrag(Point mouseLoc);
		void explode();
        bool isEqualColor(Candy &otherCandy) {return true;};
};

#endif