/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: Splashscreen.h
* Date: 13/01/2022
*/

#ifndef __SPLASHSCREEN_H
#define __SPLASHSCREEN_H

#include <Fl/Fl_PNG_Image.H>
#include <Fl/Fl_Shared_Image.H>
#include <iostream>

class Splashscreen : public Fl_PNG_Image {
public:
    Splashscreen(const char *filename);
};

#endif