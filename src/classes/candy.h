#ifndef __CANDY_H
#define __CANDY_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include "candyspeciality.h"
#include <string>

class Candy : public Fl_PNG_Image {
    const char *filename;
    Color color;
    CandySpeciality speciality;
public:
    Candy(const char *filename, Color color, CandySpeciality speciality=CandySpeciality::NONE);
    Candy(const Candy &c);
    virtual ~Candy();
    [[nodiscard]] Color getColor() const;
    [[nodiscard]] CandySpeciality getSpeciality() const;
    virtual void setColor(Color newColor);
};

#endif