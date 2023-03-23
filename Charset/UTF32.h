//
// Created by brunshweeck on 28/02/2023.
//

#ifndef CORE_UTF32_H
#define CORE_UTF32_H


#include "Unicode.h"

class UTF32 final : public Unicode {
private:
    UTF32() {
        REPLACEMENT_BYTES[0] = 0x00;
        REPLACEMENT_BYTES[1] = 0x00;
        REPLACEMENT_BYTES[2] = 0xff;
        REPLACEMENT_BYTES[3] = 0xfd;
    }

public:
    virtual Endian byteOrder() const;

    virtual Endian currentByteOrder() const;

    String name() const override;

    CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) override;

    CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    Object &clone() const override;

    void reset();

    static UTF32 INSTANCE;
private:
    gint get(ByteBuffer &src);

    static void put(gint cp, ByteBuffer &dst);

    Endian _byteOrder;

public:
};


#endif //CORE_UTF32_H
