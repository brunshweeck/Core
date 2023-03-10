//
// Created by brunshweeck on 28/02/2023.
//

#ifndef CORE_MS874_H
#define CORE_MS874_H


#include "Charset.h"

class MS874 : public Charset {
private:
    CORE_EXPLICIT MS874();

public:
    String name() const override;

    CoderResult decodeLoop(ByteBuffer &in, CharBuffer &out) override;

    CoderResult encodeLoop(CharBuffer &in, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    gbool contains(const Charset &cs) const override;

    ErrorAction malformedAction() const override;

    ErrorAction unmappableAction() const override;

    CharBuffer decode(ByteBuffer &in) override;

    ByteBuffer encode(CharBuffer &in) override;

    String toString() const override;

    Object &clone() const override;

    static MS874 INSTANCE;

private:
    static gchar decode(gint b);

    static int encode(gchar ch);
};


#endif //CORE_MS874_H
