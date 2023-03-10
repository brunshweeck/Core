//
// Created by brunshweeck on 27/02/2023.
//

#ifndef CORE_UTF16_H
#define CORE_UTF16_H


#include "Unicode.h"

class UTF16 final : public Unicode {
private:
    CORE_EXPLICIT UTF16();

public:
    String name() const override;

    ErrorAction malformedAction() const override;

    ErrorAction unmappableAction() const override;

    CoderResult decodeLoop(ByteBuffer &in, CharBuffer &out) override;

    CoderResult encodeLoop(CharBuffer &in, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    CharBuffer decode(ByteBuffer &in) override;

    ByteBuffer encode(CharBuffer &in) override;

    String toString() const override;

    gbool contains(const Charset &cs) const override;

    Object &clone() const override;

    virtual Endian currentByteOrder() const;

    virtual Endian byteOrder() const;

    static UTF16 INSTANCE;

    void reset();

private:
    gchar decode(int b1, int b2) const;

    void put(gchar c, ByteBuffer& dst) const;

    Endian _byteOrder;
};


#endif //CORE_UTF16_H
