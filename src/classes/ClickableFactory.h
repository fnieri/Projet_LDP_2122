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



class ClickableFactory : public CandyFactory, public IcingFactory {
    public:
    
        static Candy makeCandy(CandySpeciality speciality);

        static Candy makeCandy(CandySpeciality speciality, Color color);

        static Candy makeEmptyCandy();
        
        static Icing makeIcing(IcingStatus status);

        static Wall makeWall();
};


#endif