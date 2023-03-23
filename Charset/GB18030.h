//
// Created by brunshweeck on 05/03/2023.
//

#ifndef CORE_GB18030_H
#define CORE_GB18030_H


#include "Charset.h"
#include "../Character.h"

class GB18030 final : public Charset {
    GB18030() {}

public:
    String name() const override;

    CoderResult decodeLoop(ByteBuffer &src, CharBuffer &dst) override;

    CoderResult encodeLoop(CharBuffer &src, ByteBuffer &dst) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    gbool contains(const Charset &cs) const override;

    Object &clone() const override;

    static GB18030 INSTANCE;

private:
    static const String &innerDecoderIndex0;
    static const String &innerDecoderIndex1;
    static const String &innerDecoderIndex2;
    static const String &innerDecoderIndex3;
    static const String &innerDecoderIndex4;
    static const String &innerDecoderIndex5;

    static const String &innerIndex0;
    static const String &innerIndex1;
    static const String &innerIndex2;
    static const String &innerIndex3;
    static const String &innerIndex4;
    static const String &innerIndex5;
    static const String &innerIndex6;
    static const String &innerIndex7;

    static const String &innerEncoderIndex0;
    static const String &innerEncoderIndex1;
    static const String &innerEncoderIndex2;
    static const String &innerEncoderIndex3;
    static const String &innerEncoderIndex4;
    static const String &innerEncoderIndex5;
    static const String &innerEncoderIndex6;
    static const String &innerEncoderIndex7;
    static const String &innerEncoderIndex8;
    static const String &innerEncoderIndex9;
    static const String &innerEncoderIndex10;
    static const String &innerEncoderIndex11;
    static const String &innerEncoderIndex12;

    static const gshort decoderIndex1[256];
    static const String decoderIndex2[6];

    static const gshort index1[256];
    static const String index2[8];

    static const gshort encoderIndex1[256];
    static const String encoderIndex2[13];

    CORE_FAST static gchar REPLACE_CHAR = u'\uFFFD';

    static gchar getChar(int offset);

    static gchar decodeDouble(int byte1, int byte2);
};


#endif //CORE_GB18030_H
