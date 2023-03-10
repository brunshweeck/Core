//
// Created by brunshweeck on 25/02/2023.
//

#ifndef CORE_UTF8_H
#define CORE_UTF8_H

#include "Unicode.h"
#include "../IO/ByteBuffer.h"
#include "../IO/CharBuffer.h"

/*
 * Legal UTF-8 Byte Sequences
 *
 * #    Code Points      Bits   Bit/Byte pattern
 * 1                     7      0xxxxxxx
 *      U+0000..U+007F          00..7F
 *
 * 2                     11     110xxxxx    10xxxxxx
 *      U+0080..U+07FF          C2..DF      80..BF
 *
 * 3                     16     1110xxxx    10xxxxxx    10xxxxxx
 *      U+0800..U+0FFF          E0          A0..BF      80..BF
 *      U+1000..U+FFFF          E1..EF      80..BF      80..BF
 *
 * 4                     21     11110xxx    10xxxxxx    10xxxxxx    10xxxxxx
 *     U+10000..U+3FFFF         F0          90..BF      80..BF      80..BF
 *     U+40000..U+FFFFF         F1..F3      80..BF      80..BF      80..BF
 *    U+100000..U10FFFF         F4          80..8F      80..BF      80..BF
 *
 */
class UTF8 final : public Unicode {
public:
    /**
     * Construct new utf-8 charset
     */
    CORE_EXPLICIT UTF8();

    static UTF8 INSTANCE;

    /**
     * Return canonical name of this charset
     */
    String name() const override;

    ErrorAction malformedAction() const override;

    ErrorAction unmappableAction() const override;

    CoderResult decodeLoop(ByteBuffer &in, CharBuffer &out) override;

    CoderResult encodeLoop(CharBuffer &in, ByteBuffer &out) override;

    gfloat averageCharsPerByte() const override;

    gfloat averageBytesPerChar() const override;

    Object &clone() const override;

    CharBuffer decode(ByteBuffer &in) override;

    ByteBuffer encode(CharBuffer &in) override;

private:
    static gbool isNotContinuation(gint b);

    //  [E0]     [A0..BF] [80..BF]
    //  [E1..EF] [80..BF] [80..BF]
    static gbool isMalformed3(gint b1, gint b2, gint b3);

    // only used when there is only one byte left in src buffer
    static gbool isMalformed3(gint b1, gint b2);

    //  [F0]     [90..BF] [80..BF] [80..BF]
    //  [F1..F3] [80..BF] [80..BF] [80..BF]
    //  [F4]     [80..8F] [80..BF] [80..BF]
    //  only check 80-be range here, the [0xf0,0x80...] and [0xf4,0x90-...]
    //  will be checked by Character.isSupplementaryCodePoint(uc)
    static gbool isMalformed4(gint b2, gint b3, gint b4);

    // only used when there is less than 4 bytes left in src buffer.
    // both b1 and b2 should be "& 0xff" before passed in.
    static gbool isMalformed4(gint b1, gint b2);

    // tests if b1 and b2 are malformed as the first 2 bytes of a
    // legal`4-byte utf-8 byte sequence.
    // only used when there is less than 4 bytes left in src buffer,
    // after isMalformed4 has been invoked.
    static gbool isMalformed4(gint b3);
};


#endif //CORE_UTF8_H
