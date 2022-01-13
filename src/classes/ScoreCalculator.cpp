/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: ScoreCalculator.cpp
* Date: 13/01/2022
*/
        
#include "ScoreCalculator.h"

int ScoreCalculator::returnInteractionScore(Interaction currentInteraction) {
    return (int) currentInteraction;
}

int ScoreCalculator::returnCandyScore(CandySpeciality speciality) {
    switch (speciality)
    {
    case NONE:
        return 1;
    case STRIPED_HORIZONTAL:
    case STRIPED_VERTICAL:
        return 5;
    case BOMB:
        return 15;
    case MULTICOLOR:
        return 45;    
    default:
        return 0;
    }
}

int ScoreCalculator::returnIcingScore(IcingStatus status) {
    return ((int) status + 1) * 5;
}
