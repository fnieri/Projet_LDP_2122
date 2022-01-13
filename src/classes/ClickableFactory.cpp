/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: ClickableFactory.cpp
* Date: 13/01/2022
*/
        
#include "ClickableFactory.h"

Candy ClickableFactory::makeCandy(CandySpeciality speciality) {
    return generateCandy(speciality);
}

Candy ClickableFactory::makeCandy(CandySpeciality speciality, Color color) {
    return generateCandy(speciality, color);
}

Candy ClickableFactory::makeEmptyCandy() {
    return generateEmptyCandy();
}

Icing ClickableFactory::makeIcing(IcingStatus status) {
    return generateIcing(status);
}

Wall ClickableFactory::makeWall() {
    return generateWall();
}
