/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: Animation.h
* Date: 13/01/2022
*/

#ifndef __ANIMATION_H
#define __ANIMATION_H

#include "Game.h"
#include "Cell.h"

// class responsible for the animation of gravity applied to candies
class Animation : virtual public Game {
public:

    /**
     * @brief Move down cells after explosion
     * and generate new ones on top
     * 
     * @param cellsToReplace 
     */
    void moveCellsDown(vector <vector<int>> cellsToReplace) override;
    
    /**
     * @brief Move cells diagonally when needed
     * 
     * @param diagonalCells 
     * @param lr 
     */
    void moveCellsDiagonally(const vector<vector<int>> &diagonalCells, int lr) override;

    /**
     * @brief Animate cell destruction with png
     * 
     * @param cell 
     */
    static void destroyObject(Cell *cell);
};

#endif
