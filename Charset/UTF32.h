//
// Created by brunshweeck on 28/02/2023.
//

#ifndef CORE_UTF32_H
#define CORE_UTF32_H


#include "Unicode.h"

class UTF32 final : public Unicode {
private:
    CORE_EXPLICIT UTF32();

public:
    virtual Endian byteOrder() const;

    virtual Endian currentByteOrder() const;

    String name() const override;

    ErrorAction malformedAction() const override;

    ErrorAction unmappableAction() const override;

    CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) override;

    CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    CharBuffer decode(ByteBuffer &in) override;

    ByteBuffer encode(CharBuffer &in) override;

    String toString() const override;

    gbool canEncode(gchar c) const override;

    gbool contains(const Charset &cs) const override;

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
