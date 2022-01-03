#ifndef CELL_H
#define CELL_H

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>
#include <utility>

#include "Common.h"
#include "Candy.h"
#include "Enums/Color.h"
#include "Clickable.h"
#include "Enums/IcingStatus.h"
#include "Icing.h"
#include "Wall.h"

using namespace std;

class Cell {
    Point center;
    int cellSize;
    shared_ptr<Clickable> cellObjectPtr;
    int margin;
    bool drawBox = false;
    Fl_Color highlightColor = FL_LIGHT3;
public:
    Cell(Point, int, Clickable*, int);

    Cell(const Cell &);

    void castClickable(shared_ptr<Clickable>);
    void castClickable(Clickable*);
    
    bool contains(Point p) const;

    void setHighlightColor(Fl_Color);

    void draw();

    Color getColor();

    CandySpeciality getSpeciality();

    void setObject(const Clickable&);

    void setObject(Clickable*);

    //Check if current cellObjectPtr is of certain class
    template <class objectClass>
    bool isClass();

    template <class objectClass>
    bool isClass(Clickable*);
    
    template <class objectClass>
    bool isClass(const Clickable*);
    
    template <class objectClass>
    bool isClass(shared_ptr<Clickable>);

    bool hasObject();
    
    Candy* getCandy();

    Clickable* getClickable();
    
    IcingStatus getStatus();

    void animateCandy(Cell*);

    Point getCenter();

    void setCenter(Point);

    void animateGravity(Point destination);

    void setHighlighted(bool val);
    void removeObject() {cellObjectPtr = nullptr;}; 
};

#endif