/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: MainWindow.cpp
* Date: 13/01/2022
*/
        
#include "MainWindow.h"

MainWindow::MainWindow() :  Fl_Window(500, 500, 700, 700, "Candy Crush"), windowWidth{windowWidth}, windowHeight{windowHeight} {
    Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);

    resizable(this);
}

void MainWindow::draw() {
    Fl_Window::draw();
    canvas.draw();
}

int MainWindow::handle(int event) {
    if (canvas.isInputAllowed()) {
        switch (event) {
            case FL_PUSH:
                canvas.handleMouseEvent(Point{Fl::event_x(), Fl::event_y()});
                return 1;
            case FL_DRAG:
                canvas.handleMouseDrag(Point{Fl::event_x(), Fl::event_y()});
                return 1;     
            case FL_MOVE:
                canvas.highlight(Point{Fl::event_x(), Fl::event_y()});
                return 1;
            default:
                break;
        }
    }
    if (canvas.isKeyInputAllowed()) {
    switch (event)
        case FL_KEYDOWN:
            canvas.keyPressed(Fl::event_key());
            return 1;
    }
    return 0;
}

void MainWindow::Timer_CB(void *userdata) {
    MainWindow *o = (MainWindow *) userdata;
    o->redraw();
    Fl::repeat_timeout(1.0 / 60, Timer_CB, userdata);
                            //Refresh
}

