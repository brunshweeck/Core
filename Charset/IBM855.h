//
// Created by brunshweeck on 05/03/2023.
//

#ifndef CORE_IBM855_H
#define CORE_IBM855_H

#include "Charset.h"

class IBM855 final : public Charset {
    IBM855() {}

public:
    String name() const override;

    CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) override;

    CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    gbool contains(const Charset &cs) const override;

    Object &clone() const override;

    static IBM855 INSTANCE;
};

#endif //CORE_IBM855_H
