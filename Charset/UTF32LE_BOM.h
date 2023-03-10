//
// Created by brunshweeck on 04/03/2023.
//

#ifndef CORE_UTF32LE_BOM_H
#define CORE_UTF32LE_BOM_H


#include "Unicode.h"

class UTF32LE_BOM final: public Unicode {
private:
    CORE_EXPLICIT UTF32LE_BOM();

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

    static UTF32LE_BOM INSTANCE;

    CORE_FAST static gint BYTE_ORDER_MASK = (gint) 0xfffe0000;

private:
    static gint get(ByteBuffer &src);

    static void put(gint cp, ByteBuffer &dst);
};


#endif //CORE_UTF32LE_BOM_H
