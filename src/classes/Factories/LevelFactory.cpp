#include "LevelFactory.h"

enum LevelObjects {
    CANDY,
    ICING_HALF_STATUS,
    ICING_FULL_STATUS,
    WALL
};

Cell LevelFactory::buildCell(int id, Point center, int cellSize, int margin) {
    if (id == CANDY) {
        Candy candy = ClickableFactory::makeCandy(NONE);
        return {center, cellSize, &candy, margin};
    }

    else if ((id == ICING_HALF_STATUS) || (id == ICING_FULL_STATUS)) {
        Icing icing = ClickableFactory::makeIcing(static_cast<IcingStatus>(id-1));
        return {center, cellSize, &icing, margin};
    }

    else if (id == WALL) {
        Wall wall = ClickableFactory::makeWall();
        return {center, cellSize, &wall, margin};        
    }

    return {center, cellSize, nullptr, margin};
}

//https://www.cplusplus.com/doc/tutorial/files/

vector <vector <Cell> > 
    LevelFactory::buildCellVector(string filename, int margin, int cellSize, int noOfCells) {
    
    ifstream levelFile(filename);
    
    int asciiCharDiff = 48; //Digits in ascii begin
    int column = 0;
    int y = margin;
    std::string clickableID;
  
    vector <Cell> cellRow; 
    vector <vector <Cell> > cellsVector;
  
    vector <int> idRow;
    vector < vector < int >> lineInfo;

    if (levelFile.is_open()) {

        while(std::getline(levelFile, clickableID)) { 
            //Read file content line by line
            
            for (int i = 0; i < (int) clickableID.size(); i++) {
                //Push each line into a vector
                idRow.push_back((int) clickableID[i] - asciiCharDiff);
            }
     
            lineInfo.push_back(idRow);
            idRow.clear();          
        }

        for (auto &line: lineInfo) {
            //Create level from vector
            for (auto &item: line) {
                Point center{margin * column + margin, y};
                Cell cell = buildCell(item, center, cellSize, margin);
                column++;
                cellRow.push_back(cell);
            }
            y+=margin;
            column = 0;
            cellsVector.push_back(cellRow);
            cellRow.clear();
        }
    levelFile.close();
    }
    
    return cellsVector;
}