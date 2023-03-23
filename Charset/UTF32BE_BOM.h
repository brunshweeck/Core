//
// Created by brunshweeck on 04/03/2023.
//

#ifndef CORE_UTF32BE_BOM_H
#define CORE_UTF32BE_BOM_H


#include "Unicode.h"

class UTF32BE_BOM : public Unicode {
private:
    CORE_EXPLICIT UTF32BE_BOM() {
        REPLACEMENT_BYTES[0] =
        REPLACEMENT_BYTES[1] = 0x00;
        REPLACEMENT_BYTES[2] = 0xff;
        REPLACEMENT_BYTES[3] = 0xfd;
    }

public:
    String name() const override;

    CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) override;

    CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    Object &clone() const override;

    static UTF32BE_BOM INSTANCE;

    CORE_FAST static gint BYTE_ORDER_MASK = 0x0000feff;

private:
    static gint get(ByteBuffer &src);

    static void put(gint cp, ByteBuffer &dst);
};


#endif //CORE_UTF32BE_BOM_H
