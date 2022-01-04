#ifndef __SPLASHSCREEN_H
#define __SPLASHSCREEN_H

#include <Fl/Fl_PNG_Image.H>
#include <Fl/Fl_Shared_Image.H>

class Splashscreen : public Fl_PNG_Image {
public:
    Splashscreen(const char *filename);
};

#endif