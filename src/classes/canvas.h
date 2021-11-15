#ifndef __CANVAS_H
#define __CANVAS_H

#include <vector>
#include "common.h"
#include "cell.h"

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
public:
    Canvas();
    static void draw();
    static void mouseClick(Point mouseLoc);
    static void keyPressed(int keyCode);
};

#endif