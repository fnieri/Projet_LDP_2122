#ifndef __STRIPEDCANDY_H
#define __STRIPEDCANDY_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include <string>
#include "candy.h"

class StripedCandy : public Candy {	
    private:
		Fl_PNG_Image *candyIdleImage;
		Fl_PNG_Image *candyOnHoverImage;
		std::vector<Candy> neighbors;	
        bool isVertical;
    protected:
		Color color;
    public:
		StripedCandy();
		StripedCandy(Color color);
		~StripedCandy();
		bool isVertical() const;
        bool isHorizontal() const;
        void setOrientation();
        Color getColor() const;
		void setColor(Color color);
		void setImages();
		std::string generateCandyImagePrefix(Color color);
		void setIdleImage(std::string prefix);
		void setOnHoverImage(std::string prefix);
		void generateColor();
		void mouseClick(Point mouseLoc);
		void mouseMove(Point mouseLoc);
		void mouseDrag(Point mouseLoc);
		void explode();
	
};

#endif