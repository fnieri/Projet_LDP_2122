/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: MainWindow.h
* Date: 13/01/2022
*/

#ifndef __MAINWINDOW_H
#define __MAINWINDOW_H

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

#include "Canvas.h"

class MainWindow : public Fl_Window {
    const int windowWidth = 700;
    const int windowHeight = 700;
    const double refreshPerSecond = 60;

    Canvas canvas{50,60,100};
    public:
        MainWindow();
        void draw() override;
        int handle(int event);
        static void Timer_CB(void *userdata);
};

#endif