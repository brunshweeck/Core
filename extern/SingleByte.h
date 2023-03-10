//
// Created by brunshweeck on 05/03/2023.
//

#ifndef CORE_SINGLEBYTE_H
#define CORE_SINGLEBYTE_H

#include "../Charset/Charset.h"

template<gint b2cLength, gint c2bNRLength, gint c2bLength, gint c2bIndexLength>
class SingleByte final {
private:
    using B2C = gchar(&)[b2cLength + 1];
    using C2BNR = gchar(&)[c2bNRLength + 1];
    using C2B = gchar(&)[c2bLength + 1];
    using C2BINDEX = gchar(&)[c2bIndexLength + 1];

    CORE_FAST static gchar UNMAPPABLE_DECODING = u'\ufffd';
    CORE_FAST static gint UNMAPPABLE_ENCODING = 0xfffd;

public:
    CORE_EXPLICIT SingleByte() = delete;

    static gint initC2B(B2C b2c, C2BNR c2bNR, C2B c2b, C2BINDEX c2bIndex) {
        for (int i = 0; i < c2bIndexLength; i++)
            c2bIndex[i] = UNMAPPABLE_ENCODING;
        for (int i = 0; i < c2bLength; i++)
            c2b[i] = UNMAPPABLE_ENCODING;
        int off = 0;
        for (int i = 0; i < b2cLength; i++) {
            char c = b2c[i];
            if (c == UNMAPPABLE_DECODING)
                continue;
            int index = (c >> 8);
            if (c2bIndex[index] == UNMAPPABLE_ENCODING) {
                c2bIndex[index] = (char) off;
                off += 0x100;
            }
            index = c2bIndex[index] + (c & 0xff);
            c2b[index] = (char) ((i >= 0x80) ? (i - 0x80) : (i + 0x80));
        }
        if (c2bNRLength != 0) {
            // c-->b nr entries
            int i = 0;
            while (i < c2bNRLength) {
                char b = c2bNR[i++];
                char c = c2bNR[i++];
                int index = (c >> 8);
                if (c2bIndex[index] == UNMAPPABLE_ENCODING) {
                    c2bIndex[index] = (char) off;
                    off += 0x100;
                }
                index = c2bIndex[index] + (c & 0xff);
                c2b[index] = b;
            }
        }
        return 0;
    }

    //
};


#endif //CORE_SINGLEBYTE_H
