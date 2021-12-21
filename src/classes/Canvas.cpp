#include "Canvas.h"

Canvas::Canvas(int cellSize, int margin, int numberOfCells) : Board(cellSize, margin, numberOfCells) {

}

void Canvas::draw() {
    fl_color(FL_WHITE);
    fl_rectf(50, 45, 605, 605, FL_WHITE);
    fl_rect(50, 45, 605, 605, FL_BLACK);
    fl_rectf(50, 0, 605, 40, FL_WHITE);
    fl_rect(50, 0, 605, 40, FL_BLACK);

    string scoreStr = "Score: " + to_string(score);

    fl_draw(scoreStr.c_str(), 60, 20);

    // at the moment only the nearest sqrt of numberOfCells is displayed. If 20 cells, then 16 cells are shown.
    Board::draw();
}

void Canvas::keyPressed(int keyCode) {
    if (isInputAllowed()) {
        setAcceptInput(false);
        switch (keyCode) {
            case 'q':
                exit(0);
            case 'r':
                reset();
                break;
            case 'c':
                checkMatches();
                break;
            case 's':
                shuffle();
                break;
            default:
                break;
        }
    }
    setAcceptInput(true);
}

