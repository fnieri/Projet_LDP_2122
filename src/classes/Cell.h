#ifndef __CELL_H
#define __CELL_H

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

    bool isCandy();

    bool isIcing();
    
    bool isWall();

    template <class cellObject>
    shared_ptr<cellObject> returnCasted();
    
    Candy* getCandy();

    Clickable* getClickable();
    
    IcingStatus getStatus();

    void animateCandy(Cell*);

    Point getCenter();

    void setCenter(Point);

    void animateGravity(Point destination);

    void setHighlighted(bool val);

    bool isEmpty();
};

#endif