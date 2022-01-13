/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: Clickable.cpp
* Date: 13/01/2022
*/
        
#include "Clickable.h"

Clickable::Clickable(const char* filename) : Fl_PNG_Image{filename}, filename{filename} {}

Clickable::Clickable(const Clickable &c) : Fl_PNG_Image{c.filename}, filename{c.filename} {}