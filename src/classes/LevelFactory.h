#ifndef __LEVELFACTORY_H
#define __LEVELFACTORY_H


#include "Candy.h"
#include "ClickableFactory.h"
#include "Enums/IcingStatus.h"
#include "Cell.h"
#include <cstdlib>
#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

class LevelFactory{
    private:
         static Cell buildCell(int id, Point center, int cellSize, int margin);
    public:
        static
        vector<vector<Cell>> buildCellVector(string filename, int margin, int cellSize, int noOfCells);


};

#endif