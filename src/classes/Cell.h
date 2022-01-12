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
    shared_ptr<Clickable> cellClickable;
    int margin;
    bool drawBox = false;
    bool suggesting = false;
    Fl_Color highlightColor = FL_LIGHT3;
public:
    Cell(Point, int, Clickable*, int);
    Cell(const Cell &);

    //Cast arriving clickable from constructor
    void castClickable(shared_ptr<Clickable>);
    void castClickable(Clickable*);

    //Check if point is in cell
    bool contains(Point p) const;

    //Check if cell has type of clickable
    bool hasCandy();
    bool hasIcing();
    bool hasWall();
    
    //Setters
    void setCenter(Point);
    void setHighlighted(bool val);
    //Set clickable of cell
    void setClickable(const Clickable&);
    void setClickable(Clickable*);

    void setHighlightColor(Fl_Color);

    //Animation

    //Animate candy, only candy can be animated
    //Because icing and wall can't be animated
    void animateCandy(Cell*);
    //Animate gravity of cell
    void animateGravity(Point destination);
    void draw();
    void resetHighlight();
    void setSuggestion(bool suggestion);

    //Getters
    Color getColor();
    CandySpeciality getSpeciality();
    Point getCenter();
    bool isEmpty();
    Candy* getCandy();
    Clickable* getClickable();
    IcingStatus getStatus();
    
    //Return casted object from Clickable
    template <class cellObject>
    shared_ptr<cellObject> returnCasted(); 


};

#endif