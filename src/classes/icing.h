#ifndef __ICING_H
#define __ICING_H

#include <Fl/Fl_PNG_Image.H>
#include "common.h"
#include "icingstatus.h"
class Icing : public Fl_PNG_Image {
    private:
        IcingStatus status;
        Point center;
    public:
        Point getCenter();
        void setStatus(int newStatus);
        IcingStatus getStatus();
};

#endif