#ifndef __STRIPEDCANDY_H
#define __STRIPEDCANDY_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include <string>
#include "candy.h"

class StripedCandy : public Candy {	
    private:
		std::vector<Candy> neighbors;	
        bool isVertical;
		Color color;
    public:
		StripedCandy();
		StripedCandy(Color color);
		bool isVertical() const;
        bool isHorizontal() const;
        Color getColor() const;
		void mouseClick(Point mouseLoc);
		void mouseMove(Point mouseLoc);
		void mouseDrag(Point mouseLoc);
		void explode();
	
};

#endif