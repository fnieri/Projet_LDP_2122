#ifndef __LEVEL_H
#define __LEVEL_H

#include <memory>
#include <vector>
#include <stdlib.h>

class Level {
    private:
        int currentLevel;
        int boardWidth;
        int boardHeight;
        int moves;
        int bestScore;
        std::vector<std::vector<int>> walls;
        std::vector<std::vector<int>> icing;
    public:
        Level(int currentLevel, int boardWidth, int boardHeight, int moves,
              int bestScore, std::vector<std::vector<int>> walls,
              std::vector<std::vector<int>> icing);
};
#endif