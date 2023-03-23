//
// Created by brunshweeck on 04/03/2023.
//

#ifndef CORE_UTF16BE_BOM_H
#define CORE_UTF16BE_BOM_H


#include "Unicode.h"

class UTF16BE_BOM final: public Unicode {
private:
    UTF16BE_BOM() {
        REPLACEMENT_BYTES[0] = 0xff;
        REPLACEMENT_BYTES[1] = 0xfd;
    };

public:
    String name() const override;

    CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) override;

    CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    Object &clone() const override;

    static UTF16BE_BOM INSTANCE;

    CORE_FAST static gchar BYTE_ORDER_MASK = 0xfeff;

private:
    static gchar decode(int b1, int b2);

    static void put(gchar c, ByteBuffer& dst);
};


#endif //CORE_UTF16BE_BOM_H
