// These should include everything you might use
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <time.h>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "canvas.h"


using namespace std;
const int windowWidth = 700;
const int windowHeight = 700;
const double refreshPerSecond = 60;

/*--------------------------------------------------

MainWindow class.

--------------------------------------------------*/

class MainWindow : public Fl_Window {
    Canvas canvas;

public:
    MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Candy Crush") {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
    }

    void draw() override {
        Fl_Window::draw();
        canvas.draw();
    }

    int handle(int event) override {
        if (canvas.isInputAllowed()) {
            switch (event) {
                case FL_PUSH:
                
                    canvas.mouseEvent(Point{Fl::event_x(), Fl::event_y()});
                    return 1;
                
                case FL_KEYDOWN:
                
                    canvas.keyPressed(Fl::event_key());
                    return 1;

                case FL_DRAG:

                    canvas.mouseEvent(Point{Fl::event_x(), Fl::event_y()});
                    return 1;
            }
        }
        return 0;
    }

    static void Timer_CB(void *userdata) {
        MainWindow *o = (MainWindow *) userdata;
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }


};

/*--------------------------------------------------

main

Do not edit!!!!

--------------------------------------------------*/

int main(int argc, char *argv[]) {
    fl_register_images();
    srand(time(0));
    MainWindow window;
    window.show(argc, argv);
    return Fl::run();
};