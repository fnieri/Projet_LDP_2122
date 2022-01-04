#include "Icing.h"

Icing::Icing(const char* filename, IcingStatus status) : 
    Clickable{filename}, filename{filename}, status{status} {}

Icing::Icing(const Icing &i) :
    Clickable{i.filename}, filename{i.filename}, status{i.status} {}

IcingStatus Icing::getStatus() {
    return status;
}

bool Icing::isEmpty() {
    return getStatus() == IcingStatus::EMPTY;
}