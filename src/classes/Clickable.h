/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: Clickable.h
* Date: 13/01/2022
*/

#ifndef __CLICKABLE_H
#define __CLICKABLE_H

#include <Fl/Fl_PNG_Image.H>


class Clickable : public Fl_PNG_Image {
    private:
        const char* filename;
    public:
        Clickable(const char* filename);
        //Copy constructor is called by fltk everytime a new clickable is created
        Clickable(const Clickable &c);
        virtual ~Clickable()=default;
        virtual bool isEmpty() const=0;
        
        /* 
        * @brief Visitor methods to check if this method is being
        * called on a certain derived class
        * Corresponding method is reimplemented in derived classes
        */

        virtual bool visitCandy() {return false;};
        virtual bool visitIcing() {return false;};
        virtual bool visitWall() {return false;};
        
};

#endif