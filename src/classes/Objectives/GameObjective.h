#ifndef __GAMEOBJECTIVE_H
#define __GAMEOBJECTIVE_H

#include "../Game/Game.h"
#include <Fl/Fl_PNG_Image.H>


class GameObjective :virtual public Game {
    int initialNumberToAchieve;
    int currentNumberToAchieve;
    Objective currentObjective;
    unique_ptr<Candy> candyToRemove = nullptr;
    bool isComplete = false;

        //Create currentObjective
        void createObjectiveType();
        
        void makeNumberToAchieve();
        
        //Make number to achieve based on speciality
        void makeCandyNoToAchieve(CandySpeciality);
        
        void setNumberToAchieve(int min, int max);
        
        //Create candyToRemove
        Candy makeObjectiveCandy(CandySpeciality, Color);
       
        std::string getSpecialityString(CandySpeciality);
        std::string buildCandyString();     
    public:
        //Create new objective
        void objectiveInit();
        //Decrease objective based on cell sent
        void decreaseObjective(Cell);
        //Helper functions
        void decreaseCandyObjective(Cell cell);        
        void decreaseIcingObjective();
        void decreasePointObjective();

        //Getters
        bool isObjective(Objective);
        int getRemainingObjective();
        std::string getObjectiveString();
        Objective getObjective();
        bool objectiveIsComplete();

        //Check if objective is over and update
        void updateObjective();


    
};


#endif