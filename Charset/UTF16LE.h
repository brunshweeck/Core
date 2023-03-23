//
// Created by brunshweeck on 04/03/2023.
//

#ifndef CORE_UTF16LE_H
#define CORE_UTF16LE_H


#include "Unicode.h"

class UTF16LE final : public Unicode {
    UTF16LE() {
        REPLACEMENT_BYTES[0] = 0xfd;
        REPLACEMENT_BYTES[1] = 0xff;
    }

public:
    String name() const override;

    CoderResult decodeLoop(ByteBuffer &in, CharBuffer &out) override;

    CoderResult encodeLoop(CharBuffer &in, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    Object &clone() const override;

    static UTF16LE INSTANCE;

private:
    static void put(gchar c, ByteBuffer dst);

    static gchar decode(gint b1, gint b2);
};


#endif //CORE_UTF16LE_H
