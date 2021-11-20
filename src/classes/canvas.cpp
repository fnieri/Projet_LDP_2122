#include "canvas.h"

//Canvas::Canvas(Board board) : board(board) {}

Canvas::Canvas() = default;

void Canvas::draw() {
    fl_color(FL_BLACK);
    fl_draw("Fuck this shit i need sleep", 250, 20);

    // at the moment only the nearest sqrt of numberOfCells is displayed. If 20 cells, then 16 cells are shown.
    board.draw();
}

void Canvas::mouseClick(Point p) {
//    std::cout << "mouseClick" << std::endl;
//    std::cout << "x: " << p.x << " y: " << p.y << std::endl;
    if(board.contains(p)) return;
}

void Canvas::keyPressed(int keyCode) {
    switch (keyCode) {
        case 'q':
            exit(0);
    }
}
