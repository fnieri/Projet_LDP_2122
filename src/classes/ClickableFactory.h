/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: ClickableFactory.h
* Date: 13/01/2022
*/

#ifndef __CLICKABLEFACTORY_H
#define __CLICKABLEFACTORY_H

#include "Enums/CandySpeciality.h"
#include "Enums/Color.h"
#include "Candy.h"
#include "Wall.h"
#include "Icing.h"
#include "Enums/IcingStatus.h"
#include "CandyFactory.h"
#include "IcingFactory.h"
#include "WallFactory.h"


class ClickableFactory : public CandyFactory, public IcingFactory,
                         public WallFactory {
    public:
    
        static Candy makeCandy(CandySpeciality speciality);

        static Candy makeCandy(CandySpeciality speciality, Color color);

        static Candy makeEmptyCandy();
        
        static Icing makeIcing(IcingStatus status);

        static Wall makeWall();
};


#endif