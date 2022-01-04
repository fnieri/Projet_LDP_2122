#ifndef __SCORECALCULATOR_H
#define __SCORECALCULATOR_H

#include "Enums/CandySpeciality.h"
#include "Enums/IcingStatus.h"
#include "Enums/Interaction.h"

class ScoreCalculator {

    public:
        static int returnInteractionScore(Interaction);
        static int returnCandyScore(CandySpeciality);
        static int returnIcingScore(IcingStatus);

};

#endif