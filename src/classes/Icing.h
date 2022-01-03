#ifndef __ICING_H
#define __ICING_H

#include <Fl/Fl_PNG_Image.H>
#include "Common.h"
#include "IcingStatus.h"
#include "Clickable.h"

class Icing : public Clickable {
    private:
        const char* filename;
        IcingStatus status;
    public:
        ~Icing()=default;
        Icing(const char* filename, IcingStatus status);
        Icing(const Icing &i);
        IcingStatus getStatus();
};

#endif