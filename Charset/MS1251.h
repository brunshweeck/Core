//
// Created by brunshweeck on 28/02/2023.
//

#ifndef CORE_MS1251_H
#define CORE_MS1251_H

#include "Charset.h"

class MS1251 final : public Charset {
    MS1251() {}

public:
    String name() const override;

    CoderResult decodeLoop(ByteBuffer &in, CharBuffer &out) override;

    CoderResult encodeLoop(CharBuffer &in, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    gbool contains(const Charset &cs) const override;

    Object &clone() const override;

    static MS1251 INSTANCE;

private:
    static gchar decode(gint b);

    static int encode(gchar ch);
};


#endif //CORE_MS1251_H
