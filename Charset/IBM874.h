//
// Created by brunshweeck on 05/03/2023.
//

#ifndef CORE_IBM874_H
#define CORE_IBM874_H


#include "Charset.h"

class IBM874 final: public Charset {
private:
    CORE_EXPLICIT IBM874();

public:
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

    gbool contains(const Charset &cs) const override;

    gbool canEncode(gchar c) const override;

    Object &clone() const override;

    static IBM874 INSTANCE;
};

#endif //CORE_IBM874_H
