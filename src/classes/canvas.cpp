#include "canvas.h"

Canvas::Canvas() = default;

void Canvas::draw() {
    fl_color(FL_BLACK);
    fl_draw("jeffery", 350, 20);

    fl_color(FL_WHITE);
    fl_rect(55, 45, 605, 605, FL_BLACK);
    fl_rectf(55, 45, 600, 600, FL_WHITE);

    // at the moment only the nearest sqrt of numberOfCells is displayed. If 20 cells, then 16 cells are shown.
    board.draw();
}

void Canvas::mouseClick(Point p) {
//    board.checkMatches();
    if (board.contains(p)) return;
}

void Canvas::mouseDrag(Point p) {
    board.handleDrag(p);
}

void Canvas::keyPressed(int keyCode) {
    switch (keyCode) {
        case 'q':
            exit(0);
        case 'c':
            board.checkMatches();
            break;
        case 'r':
            board.reset();
            break;
    }
}
