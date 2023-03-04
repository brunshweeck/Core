//
// Created by brunshweeck on 25/02/2023.
//

#ifndef CORE_UNICODE_H
#define CORE_UNICODE_H


#include "Charset.h"

class Unicode : public Charset {
public:
    enum Endian : gbyte {
        NONE,
        BIG,
        LITTLE
    };
    /**
     * Construct new Unicode charset
     */
    CORE_EXPLICIT Unicode(const String &name);

    /**
     * Tells whether or not this charset contains the given charset.
     */
    gbool contains(const Charset &cs) const override;
};


#endif //CORE_UNICODE_H
