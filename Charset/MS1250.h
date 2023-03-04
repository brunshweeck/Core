//
// Created by brunshweeck on 28/02/2023.
//

#ifndef CORE_MS1250_H
#define CORE_MS1250_H


#include "Charset.h"

class MS1250 final : public Charset {
private:
    CORE_EXPLICIT MS1250();

public:

    String name() const override;

    CoderResult decodeLoop(ByteBuffer &in, CharBuffer &out) override;

    CoderResult encodeLoop(CharBuffer &in, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    gbool contains(const Charset &cs) const override;

    Object &clone() const override;

    CharBuffer decode(ByteBuffer &in) override;

    ByteBuffer encode(CharBuffer &in) override;

    static MS1250 INSTANCE;

private:
    static gchar decode(gint b);

    static int encode(gchar ch);
};


#endif //CORE_MS1250_H
