/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: 
* Date: 13/01/2022
*/

#ifndef __ICINGFACTORY_H
#define __ICINGFACTORY_H


#include "Enums/IcingStatus.h"
#include "Icing.h"
#include <cstdlib>
#include <cstring>


class IcingFactory {
    private:

        static std::string
            generateIcingPath(IcingStatus status);

    public:
        static Icing generateIcing(IcingStatus status);
};
#endif