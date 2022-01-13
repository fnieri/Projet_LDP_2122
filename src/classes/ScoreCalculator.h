/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: ScoreCalculator.h
* Date: 13/01/2022
*/

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