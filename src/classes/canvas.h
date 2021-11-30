#ifndef __CANVAS_H
#define __CANVAS_H

#include <vector>
#include "common.hpp"
#include "cell.h"
#include "board.h"
#include "board.h"
#include <cmath>
#include <iostream>
#include <FL/fl_draw.H>


/*--------------------------------------------------

Canvas class.

One instance of the canvas class is made by the
MainWindow class.

The fltk system via MainWindow calls:

draw 60 times a second
mouseClick whenever the mouse is clicked
keyPressed whenever a key is pressed

Any drawing code should be called ONLY in draw
or methods called by draw. If you try to draw
elsewhere it will probably crash.
--------------------------------------------------*/

class Canvas {
    Board board{50,60,100};
public:
    Canvas();
    void draw();
    void mouseClick(Point mouseLoc);
    void mouseDrag(Point p);
    void keyPressed(int keyCode);

    void handleRelease();
};

#endif