//
// Created by brunshweeck on 05/03/2023.
//

#ifndef CORE_IBM437_H
#define CORE_IBM437_H


#include "Charset.h"

class IBM437 final : public Charset {
    IBM437() {}

public:
    String name() const override;

    CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) override;

    CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    gbool contains(const Charset &cs) const override;

    Object &clone() const override;

    static IBM437 INSTANCE;
};


#endif //CORE_IBM437_H
