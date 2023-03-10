//
// Created by brunshweeck on 04/03/2023.
//

#ifndef CORE_UTF16LE_H
#define CORE_UTF16LE_H


#include "Unicode.h"

class UTF16LE final : public Unicode {
private:
    CORE_EXPLICIT UTF16LE();

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

    Object &clone() const override;

    static UTF16LE INSTANCE;

private:
    static void put(gchar c, ByteBuffer dst);

    static gchar decode(gint b1, gint b2);
};


#endif //CORE_UTF16LE_H
