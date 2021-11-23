#include "candy.h"

Candy::Candy(const char *filename, Point center) : Fl_PNG_Image(filename), center(center), filename(filename) {}

Candy::Candy(const Candy &c) : Fl_PNG_Image{c.filename}, center{c.center}, filename(c.filename) {}
