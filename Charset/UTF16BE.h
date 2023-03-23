//
// Created by brunshweeck on 04/03/2023.
//

#ifndef CORE_UTF16BE_H
#define CORE_UTF16BE_H


#include "Unicode.h"

class UTF16BE final : public Unicode {
    UTF16BE() {
        REPLACEMENT_BYTES[0] = 0xff;
        REPLACEMENT_BYTES[1] = 0xfd;
    };

public:
    String name() const override;

    CoderResult decodeLoop(ByteBuffer &in, CharBuffer &out) override;

    CoderResult encodeLoop(CharBuffer &in, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    Object &clone() const override;

    static UTF16BE INSTANCE;

private:
    static gchar decode(gint b1, gint b2);

    static void put(gchar c, ByteBuffer dst);
};


#endif //CORE_UTF16BE_H
