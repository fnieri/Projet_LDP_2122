#ifndef __CLICKABLEFACTORY_H
#define __CLICKABLEFACTORY_H

#include "../Enums/CandySpeciality.h"
#include "../Enums/Color.h"
#include "../Clickables/Candy.h"
#include "../Clickables/Wall.h"
#include "../Clickables/Icing.h"
#include "../Enums/IcingStatus.h"
#include "../Factories/CandyFactory.h"
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