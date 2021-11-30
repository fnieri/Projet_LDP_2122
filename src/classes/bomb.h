#ifndef __BOMB_H
#define __BOMB_H

#include <Fl/Fl_PNG_Image.H>
#include "common.hpp"
#include "color.h"
#include <string>
#include "candy.h"

class Bomb : public Candy {	
    private:
		std::vector<Candy> neighbors;	
    	Color color;
    public:
		Bomb();
		Bomb(Color color);
		Color getColor();
		void mouseClick(Point mouseLoc);
		void mouseMove(Point mouseLoc);
		void mouseDrag(Point mouseLoc);
		void explode();
	
};

#endif