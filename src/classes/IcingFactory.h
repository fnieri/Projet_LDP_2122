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