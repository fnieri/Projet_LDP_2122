#ifndef __SCORECALCULATOR_H
#define __SCORECALCULATOR_H

#include "CandySpeciality.h"

enum Interaction {
    NONE_MULTICOLOR = 5,
    DOUBLE_STRIPED = 10,
    STRIPED_WRAPPED = 15,
    STRIPED_MULTICOLOR = 30,
    DOUBLE_WRAPPED = 25,
    WRAPPED_MULTICOLOR = 45,
    DOUBLE_MULTICOLOR = 100
};

class ScoreCalculator {

    public:
        int returnInteractionScore(Interaction);
        int returnCandyScore(CandySpeciality);
};

#endif