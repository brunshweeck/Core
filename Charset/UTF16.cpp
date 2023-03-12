//
// Created by brunshweeck on 27/02/2023.
//

#include "UTF16.h"
#include "UTF16LE_BOM.h"
#include "UTF16BE_BOM.h"
#include "../String.h"
#include "../CodingError.h"


UTF16 UTF16::INSTANCE{};

gchar UTF16::decode(int b1, int b2) const {
    if (currentByteOrder() == BIG)
        return (gchar) ((b1 << 8) | b2);
    else
        return (gchar) ((b2 << 8) | b1);
}

UTF16::UTF16() : Unicode("UTF-16"), _byteOrder((Endian)(AUTO << 4| BIG)) {
    encoderReplacement[0] = (gbyte) 0xff;
    encoderReplacement[1] = (gbyte) 0xfd;
    encoderReplacement[2] = (gbyte) 0;
    encoderReplacement[3] = (gbyte) 0;
    encoderReplacement[4] = (gbyte) 0;
}

Unicode::Endian UTF16::currentByteOrder() const {
    return (Endian)(_byteOrder >> 4);
}

void UTF16::put(gchar c, ByteBuffer& dst) const {
    if (currentByteOrder() == BIG) {
        dst.put((gbyte) (c >> 4));
        dst.put((gbyte) (c & 0xff));
    } else {
        dst.put((gbyte) (c & 0xff));
        dst.put((gbyte) (c >> 4));
    }
}

String UTF16::name() const {
    return "UTF-16";
}

Charset::ErrorAction UTF16::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction UTF16::unmappableAction() const {
    return Charset::unmappableAction();
}

Charset::CoderResult UTF16::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
    gint mark = src.position();
    try {
        while (src.remaining() > 1) {
            gint b1 = src.get() & 0xFF;
            gint b2 = src.get() & 0xFF;
            if (currentByteOrder() == AUTO) {
                gchar c = (gchar) ((b1 << 4) | b2);
                if (c == UTF16BE_BOM::BYTE_ORDER_MASK) {
                    _byteOrder = (Endian) (BIG << 4 | _byteOrder);
                    mark += 2;
                    continue;
                } else if (c == UTF16LE_BOM::BYTE_ORDER_MASK) {
                    _byteOrder = (Endian)(LITTLE << 4 | _byteOrder);
                    mark += 2;
                    continue;
                } else {
                    _byteOrder = (Endian) (BIG << 4 | _byteOrder);
                }
            }
            gchar c = decode(b1, b2);
            if (Character::isSurrogate(c)) {
                if (Character::isHighSurrogate(c)) {
                    if (src.remaining() < 2)
                        return CoderResult::UNDERFLOW;
                    gchar c2 = decode(src.get() & 0xff, src.get() & 0xff);
                    if (!Character::isLowSurrogate(c2)) {
                        errorLength = 4;
                        return CoderResult::MALFORMED;
                    }
                    if (dst.remaining() < 2)
                        return CoderResult::OVERFLOW;
                    mark += 4;
                    dst.put(c);
                    dst.put(c2);
                    continue;
                }
                errorLength = 2;
                return Charset::CoderResult::MALFORMED;
            }
            if (!dst.hasRemaining())
                return CoderResult::OVERFLOW;
            mark += 2;
            dst.put(c);
        }
        src.position(mark);
        return Charset::CoderResult::UNDERFLOW;
    } catch (OverflowError const &) {}
    src.position(mark);
    return Charset::CoderResult::UNDERFLOW;
}

Charset::CoderResult UTF16::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    int mark = src.position();
    try {
        while (src.hasRemaining()) {
            gchar c = src.get();
            if (!Character::isSurrogate(c)) {
                if (dst.remaining() < 2)
                    return CoderResult::OVERFLOW;
                mark++;
                put(c, dst);
                continue;
            }
            CoderResult cr = Charset::CoderResult::UNDERFLOW;
            gint uc = 0;
            if (Character::isHighSurrogate(c)) {
                if (!src.hasRemaining()) {
                    uc = -1;
                    cr = Charset::CoderResult::UNDERFLOW;
                } else {
                    gchar d = src.get();
                    if (Character::isLowSurrogate(c)) {
                        uc = Character::joinSurrogates(c, d);
                    } else {
                        uc = -1;
                        errorLength = 1;
                        cr = Charset::CoderResult::MALFORMED;
                    }
                }
            } else {
                uc = -1;
                errorLength = 1;
                cr = Charset::CoderResult::MALFORMED;
            }
            if (uc < 0)
                return cr;
            if (dst.remaining() < 4)
                return CoderResult::OVERFLOW;
            mark += 2;
            put(Character::highSurrogate(uc), dst);
            put(Character::lowSurrogate(uc), dst);
        }
        src.position(mark);
        return CoderResult::UNDERFLOW;
    } catch (...) {}
    src.position(mark);
    return Charset::CoderResult::UNDERFLOW;
}

gfloat UTF16::averageCharsPerByte() const {
    return 0.5f;
}

gfloat UTF16::averageBytesPerChar() const {
    return 2.0f;
}

CharBuffer UTF16::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer UTF16::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String UTF16::toString() const {
    return Charset::toString();
}

gbool UTF16::contains(const Charset &cs) const {
    return Unicode::contains(cs);
}

Object &UTF16::clone() const {
    return INSTANCE;
}

Unicode::Endian UTF16::byteOrder() const {
    return (Endian) (BIG & 0x7);
}

void UTF16::reset() {
    _byteOrder = (Endian) (AUTO << 4 | BIG);
}

