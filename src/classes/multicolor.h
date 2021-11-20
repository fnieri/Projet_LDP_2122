#ifndef __BOMB_H
#define __BOMB_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include <string>
#include "candy.h"

class MultiColor : public Candy {	
    private:
		Fl_PNG_Image *candyIdleImage;
		Fl_PNG_Image *candyOnHoverImage;
		std::vector<Candy> neighbors;	
    protected:
		Color color;
    public:
		MultiColor();
		~MultiColor();
		Color getColor();
		void setImages();
		std::string generateCandyImagePrefix(Color color);
		void setIdleImage(std::string prefix);
		void setOnHoverImage(std::string prefix);
		void mouseClick(Point mouseLoc);
		void mouseMove(Point mouseLoc);
		void mouseDrag(Point mouseLoc);
		void explode();
        bool isEqualColor(Candy &otherCandy) {return true;};
};

#endif