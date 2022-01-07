#ifndef __CANDY_H
#define __CANDY_H

#include <Fl/Fl_PNG_Image.H>
#include "Common.h"
#include "Enums/Color.h"
#include "Enums/CandySpeciality.h"
#include "Clickable.h"

class Candy :  public Clickable {
    const char *filename;
    Color color;
    CandySpeciality speciality;
public:
    Candy(const char *filename, Color color, CandySpeciality speciality=CandySpeciality::NONE);
    Candy(const Candy &c);
    ~Candy();
    [[nodiscard]] Color getColor() const;
    [[nodiscard]] CandySpeciality getSpeciality() const;

    bool isEmpty() const override;
    bool visitCandy() override {return true;};
};

#endif