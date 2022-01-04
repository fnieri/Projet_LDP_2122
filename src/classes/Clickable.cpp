#include "Clickable.h"

Clickable::Clickable(const char* filename) : Fl_PNG_Image{filename}, filename{filename} {}

Clickable::Clickable(const Clickable &c) : Fl_PNG_Image{c.filename}, filename{c.filename} {}