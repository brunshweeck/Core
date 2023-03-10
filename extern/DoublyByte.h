//
// Created by brunshweeck on 05/03/2023.
//

#ifndef CORE_DOUBLYBYTE_H
#define CORE_DOUBLYBYTE_H


#include "../Charset/Charset.h"

template<gint b2cLength, gint c2bNRLength, gint c2bLength, gint c2bIndexLength>
class DoublyByte final {
private:
    using B2C = gchar const*(&)[b2cLength + 1];
    using C2BNR = gchar(&)[c2bNRLength + 1];
    using C2B = gchar(&)[c2bLength + 1];
    using C2BINDEX = gchar(&)[c2bIndexLength + 1];

    CORE_FAST static gchar UNMAPPABLE_DECODING = u'\ufffd';
    CORE_FAST static gint UNMAPPABLE_ENCODING = 0xfffd;

public:
    CORE_EXPLICIT DoublyByte() = delete;

    static gint initC2B(B2C b2cStr, C2BNR c2bNR, C2B c2b, C2BINDEX c2bIndex) {
        return 0;
    }

    //
};

#endif //CORE_DOUBLYBYTE_H
