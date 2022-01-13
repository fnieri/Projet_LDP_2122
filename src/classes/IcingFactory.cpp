/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: IcingFactory.cpp
* Date: 13/01/2022
*/
        
#include "IcingFactory.h"

std::string IcingFactory::generateIcingPath(IcingStatus status) {
    if (status == COMPLETE_ICING) 
        return "/sprites/icing/icing_2.png";
    else if(status ==HALF_ICING)
        return "/sprites/icing/icing_1.png";
    return "";
}

Icing IcingFactory::generateIcing(IcingStatus status) {
    std::string filename = WORKING_DIRECTORY + generateIcingPath(status);
    char *fullPathChar = new char[filename.length() + 1];
    strcpy(fullPathChar, filename.c_str());
    return {fullPathChar, status};
}