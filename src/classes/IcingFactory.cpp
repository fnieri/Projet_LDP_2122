#include "IcingFactory.h"

std::string IcingFactory::generateIcingPath(IcingStatus status) {
        if (status == COMPLETE_ICING) 
        return "/sprites/icing/icing_2.png";
    return "/sprites/icing/icing_1.png";
}

Icing IcingFactory::generateIcing(IcingStatus status) {
    std::string filename = WORKING_DIRECTORY + generateIcingPath(status);
    char *fullPathChar = new char[filename.length() + 1];
    strcpy(fullPathChar, filename.c_str());
    return {fullPathChar, status};
}