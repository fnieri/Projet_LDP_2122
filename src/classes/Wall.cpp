#include "Wall.h"

Wall::Wall(const char* filename) :
    Clickable{filename}, filename{filename} {}


Wall::Wall(const Wall &w) : Clickable{w.filename}, filename{w.filename} {}

bool Wall::isEmpty() const  {
    return false;
}