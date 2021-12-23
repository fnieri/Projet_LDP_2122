#ifndef __CLICKABLE_H
#define __CLICKABLE_H

#include <Fl/Fl_PNG_Image.H>


class Clickable : public Fl_PNG_Image {
    private:
        const char* filename;
    public:
        Clickable(const char* filename);
        Clickable(const Clickable &c);
        virtual ~Clickable()=default;
};

#endif