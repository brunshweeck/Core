//
// Created by brunshweeck on 05/03/2023.
//

#ifndef CORE_ISO8859_2_H
#define CORE_ISO8859_2_H


#include "Charset.h"

class ISO8859_2 final : public Charset {
    ISO8859_2() {}

public:
    String name() const override;

    ErrorAction malformedAction() const override;

    ErrorAction unmappableAction() const override;

    CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) override;

    CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    gbool contains(const Charset &cs) const override;

    Object &clone() const override;

    static ISO8859_2 INSTANCE;
};


#endif //CORE_ISO8859_2_H
