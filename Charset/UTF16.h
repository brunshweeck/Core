//
// Created by brunshweeck on 27/02/2023.
//

#ifndef CORE_UTF16_H
#define CORE_UTF16_H


#include "Unicode.h"

class UTF16 final : public Unicode {
    UTF16() {
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

    virtual Endian currentByteOrder() const;

    virtual Endian byteOrder() const;

    static UTF16 INSTANCE;

    /**
     * Return current byte order
     * It must be call it before any coding operation with this instance
     */
    void reset();

private:
    gchar decode(int b1, int b2) const;

    void put(gchar c, ByteBuffer &dst) const;

    Endian _byteOrder;
};


#endif //CORE_UTF16_H
