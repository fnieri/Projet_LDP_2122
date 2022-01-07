#ifndef __ICING_H
#define __ICING_H

#include <Fl/Fl_PNG_Image.H>
#include "../Sources/Common.h"
#include "../Enums/IcingStatus.h"
#include "Clickable.h"

class Icing : public Clickable {
    private:
        const char* filename;
        IcingStatus status;

    public:
        ~Icing()=default;
        Icing(const char* filename, IcingStatus status);
        Icing(const Icing &i);
        IcingStatus getStatus() const;
        bool isEmpty() const override;
        bool visitIcing() override {return true;};
};

#endif