#ifndef __CANDY_H
#define __CANDY_H

#include <Fl/Fl_PNG_Image.H>
#include <Fl/Fl_Shared_Image.H>
#include "Common.h"
#include "Color.h"
#include "CandySpeciality.h"

class Candy : public Fl_PNG_Image {
    const char *filename;
    Color color;
    CandySpeciality speciality;
public:
    Candy(const char *filename, Color color, CandySpeciality speciality=CandySpeciality::NONE);
    Candy(const Candy &c);
    virtual ~Candy();
    void setSize(int size);
    [[nodiscard]] Color getColor() const;
    [[nodiscard]] CandySpeciality getSpeciality() const;
    virtual void setColor(Color newColor);
};

#endif