#include "canvas.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <FL/fl_draw.H>

Canvas::Canvas() = default;

void Canvas::draw() {
    fl_color(FL_BLACK);
    fl_draw("Fuck this shit i need sleep", 250, 20);

    // create a vector of cells
    vector<Cell> CellsVertex; // unused

    int cellSize = 50;
    int y = 60;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            Point center{60 + j * 60, y};
            Cell(center, cellSize).draw();
        }
        y += 60;
    }

}

void Canvas::mouseClick(Point /*mouseLoc*/) {
    std::cout << "mouseClick" << std::endl;
}

void Canvas::keyPressed(int keyCode) {
    switch (keyCode) {
        case 'q':
            exit(0);
    }
}
