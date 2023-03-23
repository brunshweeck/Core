//
// Created by brunshweeck on 04/03/2023.
//

#ifndef CORE_UTF32LE_BOM_H
#define CORE_UTF32LE_BOM_H


#include "Unicode.h"

class UTF32LE_BOM final : public Unicode {
    UTF32LE_BOM() {
        REPLACEMENT_BYTES[0] = 0xfd;
        REPLACEMENT_BYTES[1] = 0xff;
        REPLACEMENT_BYTES[2] =
        REPLACEMENT_BYTES[3] = 0x00;
    }

public:
    String name() const override;

    CoderResult decodeLoop(ByteBuffer &in, CharBuffer &out) override;

    CoderResult encodeLoop(CharBuffer &in, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    Object &clone() const override;

    static UTF32LE_BOM INSTANCE;

    CORE_FAST static gint BYTE_ORDER_MASK = (gint) 0xfffe0000;

private:
    static gint get(ByteBuffer &src);

    static void put(gint cp, ByteBuffer &dst);
};


#endif //CORE_UTF32LE_BOM_H
