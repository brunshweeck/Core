//
// Created by brunshweeck on 04/03/2023.
//

#ifndef CORE_UTF32LE_H
#define CORE_UTF32LE_H


#include "Unicode.h"

class UTF32LE final: public Unicode {
private:
    CORE_EXPLICIT UTF32LE();

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

    gbool canEncode(gchar c) const override;

    gbool contains(const Charset &cs) const override;

    Object &clone() const override;

    static UTF32LE INSTANCE;

private:
    static gint get(ByteBuffer &src);

    static void put(gint cp, ByteBuffer &dst);
};


#endif //CORE_UTF32LE_H
