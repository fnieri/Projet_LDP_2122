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
        virtual bool visitCandy()=0;
        virtual bool visitIcing()=0;
        virtual bool visitWall()=0;
        virtual bool isEmpty() const=0;
};

#endif