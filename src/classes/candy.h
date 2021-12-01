#ifndef __CANDY_H
#define __CANDY_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "color.h"
#include <string>

class Candy : public Fl_PNG_Image {
    const char *filename;
    Color color;
public:
    Candy(const char *filename, Color color);
    Candy(const Candy &c);
    virtual ~Candy();
    [[nodiscard]] Color getColor() const;
    virtual void setColor(Color newColor);
    void handleMove();

    void showNormal();

};

#endif
