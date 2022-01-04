#ifndef __GAMEOBJECTIVE_H
#define __GAMEOBJECTIVE_H

#include "Game.h"
#include <Fl/Fl_PNG_Image.H>


class GameObjective :virtual public Game {
    int initialNumberToAchieve;
    int currentNumberToAchieve;
    Objective currentObjective;
    unique_ptr<Candy> candyToRemove = nullptr;
    bool isComplete = false;

    void createObjective();
    
    void makeNumberToAchieve();
    
    void makeCandyNoToAchieve(CandySpeciality);
    
    void setNumberToAchieve(int min, int max);
    
    Candy makeObjectiveCandy(CandySpeciality, Color);
    public:
        void objectiveInit();
        
        void decreaseCandyObjective(Cell cell);        
        
        void decreaseIcingObjective();     

        void decreasePointObjective();

        void decreaseObjective(Cell);

        bool isObjective(Objective);

        int getRemainingObjective();

        std::string getObjectiveString();

        Objective getObjective();

        std::string getSpecialityString(CandySpeciality);
        
        void updateObjective();

        bool objectiveIsComplete();

        std::string buildCandyString();
        
};


#endif