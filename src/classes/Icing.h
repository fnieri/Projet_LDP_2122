/* LDP INFO-F-202 First Session project.
* Authors: Louis Vanstappen, Francesco Nieri
*               515205          515694
* Header: Icing.h
* Date: 13/01/2022
*/

#ifndef __ICING_H
#define __ICING_H

#include <Fl/Fl_PNG_Image.H>
#include "Common.h"
#include "Enums/IcingStatus.h"
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