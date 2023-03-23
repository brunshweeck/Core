//
// Created by brunshweeck on 04/03/2023.
//

#ifndef CORE_US_ASCII_H
#define CORE_US_ASCII_H


#include "Charset.h"

class US_ASCII final : public Charset {
    US_ASCII() {}

public:
    String name() const override;

    CoderResult decodeLoop(ByteBuffer &in, CharBuffer &out) override;

    CoderResult encodeLoop(CharBuffer &in, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    gbool contains(const Charset &cs) const override;

    Object &clone() const override;

    static US_ASCII INSTANCE;
};


#endif //CORE_US_ASCII_H
