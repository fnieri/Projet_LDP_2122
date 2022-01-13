/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Source code: Icing.cpp
* Date: 13/01/2022
*/
        
#include "Icing.h"

Icing::Icing(const char* filename, IcingStatus status) : 
    Clickable{filename}, filename{filename}, status{status} {}

Icing::Icing(const Icing &i) :
    Clickable{i.filename}, filename{i.filename}, status{i.status} {}

IcingStatus Icing::getStatus() const {
    return status;
}

bool Icing::isEmpty() const {
    return getStatus() == IcingStatus::EMPTY;
}