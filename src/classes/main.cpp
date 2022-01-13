/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: main.cpp
* Date: 13/01/2022
*/
        
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    fl_register_images();
    srand(time(0));
    MainWindow window;
    window.show(argc, argv);
    return Fl::run();
};