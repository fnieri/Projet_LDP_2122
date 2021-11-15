//
// Created by louis on 11/15/21.
//

#ifndef __COMMON_H
#define __COMMON_H
#include <color.hpp>
#include <iostream>
#include <filesystem>
struct Point {
    int x, y;
};

#define NUMBER_OF_COLORS 6
#define CANDY_IDLE_IMAGE_EXTENSION "_01.png"
#define CANDY_ON_HOVER_IMAGE_EXTENSION "_02.png"
#define SUPER_CANDY_HORIZONTAL_EXTENSION "_horizontal.png"
#define SUPER_CANDY_VERTICAL_EXTENSION "_vertical.png"
#define SUPER_CANDY_BOMB_EXTENSION "_bomb.png"

int ass() {
    std::cout << WORKING_PATH;
}
#endif
