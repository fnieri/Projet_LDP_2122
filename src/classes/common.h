//
// Created by louis on 11/15/21.
//

#ifndef __COMMON_H
#define __COMMON_H
#include <iostream>
#include <experimental/filesystem>


class Board;
class MatchDetection;   //We define classes now because they are interdependent,
//so they need to know the existence of the other class 


struct Point {
    int x, y;
};

//std::string CURRENT_PATH = std::experimental::filesystem::current_path();

#define NUMBER_OF_COLORS 6
#define CANDY_IDLE_IMAGE_EXTENSION "_01.png"
#define CANDY_ON_HOVER_IMAGE_EXTENSION "_02.png"
#define SUPER_CANDY_HORIZONTAL_EXTENSION "_horizontal.png"
#define SUPER_CANDY_VERTICAL_EXTENSION "_vertical.png"
#define SUPER_CANDY_BOMB_EXTENSION "_bomb.png"
#define WORKING_DIRECTORY std::string(std::experimental::filesystem::current_path())


#endif
