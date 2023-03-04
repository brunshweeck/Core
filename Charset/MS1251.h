//
// Created by brunshweeck on 28/02/2023.
//

#ifndef CORE_MS1251_H
#define CORE_MS1251_H

#include "Charset.h"

class MS1251: public Charset {
public:
    CORE_EXPLICIT MS1251();

    String name() const override;

    CoderResult decodeLoop(ByteBuffer &in, CharBuffer &out) override;

    CoderResult encodeLoop(CharBuffer &in, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    gbool contains(const Charset &cs) const override;

    Object &clone() const override;



private:
    static gchar decode(gint b);
    static int encode(gchar ch);
};


#endif //CORE_MS1251_H
