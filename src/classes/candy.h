#ifndef __CANDY_H
#define __CANDY_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include <string>
#include "candyspeciality.h"


class Candy : public Fl_PNG_Image {
    private:
        const char *filename;
        Color color;
        CandySpeciality speciality;
    public:
        Candy(const char *filename, Color color, CandySpeciality speciality);
        Candy(const Candy &c);
        Color getColor() const;
        CandySpeciality getSpeciality();
};
#endif
