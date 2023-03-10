//
// Created by brunshweeck on 28/02/2023.
//

#include "UTF32.h"
#include "UTF32LE_BOM.h"
#include "UTF32BE_BOM.h"
#include "../String.h"

UTF32::UTF32() : Unicode("UTF-32"), _byteOrder((Endian)(AUTO << 4 | BIG)) {
    encoderReplacement[0] = (gbyte) 0;
    encoderReplacement[1] = (gbyte) 0;
    encoderReplacement[2] = (gbyte) 0xff;
    encoderReplacement[3] = (gbyte) 0xfd;
    encoderReplacement[4] = (gbyte) 0;
}

UTF32 UTF32::INSTANCE{};

Unicode::Endian UTF32::byteOrder() const {
    return (Endian)(_byteOrder & 0x7);
}

Unicode::Endian UTF32::currentByteOrder() const {
    return (Endian)(_byteOrder >> 4);
}

gint UTF32::get(ByteBuffer &src) {
    return ((Endian)(_byteOrder >> 4) == BIG) ?
           (((src.get() & 0xff) << 24) | ((src.get() & 0xff) << 16) |
            ((src.get() & 0xff) << 8) | (src.get() & 0xff)) :
           ((src.get() & 0xff) | ((src.get() & 0xff) << 8) |
            ((src.get() & 0xff) << 16) | ((src.get() & 0xff) << 24));
}

void UTF32::put(gint cp, ByteBuffer &dst) {
    dst.put((gbyte) (cp >> 24));
    dst.put((gbyte) (cp >> 16));
    dst.put((gbyte) (cp >> 8));
    dst.put((gbyte) cp);
}

void UTF32::reset() {
    _byteOrder = (Endian)(AUTO << 4 | BIG);
}

String UTF32::name() const {
    return "UTF-32";
}

Charset::ErrorAction UTF32::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction UTF32::unmappableAction() const {
    return Charset::unmappableAction();
}

Charset::CoderResult UTF32::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
    if (src.remaining() < 4)
        return CoderResult::UNDERFLOW;
    gint mark = src.position();
    gint cp;
    try {
        if ((Endian)(_byteOrder >> 4) == AUTO) {
            cp = ((src.get() & 0xff) << 24) | ((src.get() & 0xff) << 16) |
                 ((src.get() & 0xff) << 8) | (src.get() & 0xff);
            if (cp == UTF32BE_BOM::BYTE_ORDER_MASK && _byteOrder != LITTLE) {
                _byteOrder = (Endian)(BIG << 4 | _byteOrder);
                mark += 4;
            } else if (cp == UTF32LE_BOM::BYTE_ORDER_MASK && _byteOrder != BIG) {
                _byteOrder = (Endian)(LITTLE << 4 | _byteOrder);
                mark += 4;
            } else {
                _byteOrder = (Endian)(BIG << 4 | _byteOrder);
                src.position(mark);
            }
        }
        while (src.remaining() >= 4) {
            cp = get(src);
            if (0 <= cp && cp <= 0xFFFF) {
                if (!dst.hasRemaining())
                    return CoderResult::OVERFLOW;
                mark += 4;
                dst.put((gchar) cp);
            } else if (Character::isValidCodePoint(cp)) {
                if (dst.remaining() < 2)
                    return CoderResult::OVERFLOW;
                mark += 4;
                dst.put(Character::highSurrogate(cp));
                dst.put(Character::lowSurrogate(cp));
            } else {
                errorLength = 4;
                return CoderResult::MALFORMED;
            }
        }
        src.position(mark);
        return CoderResult::UNDERFLOW;
    } catch (...) {}
    src.position(mark);
    return Charset::CoderResult::UNDERFLOW;
}

Charset::CoderResult UTF32::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    gint mark = src.position();
    try {
        while (src.hasRemaining()) {
            gchar c = src.get();
            if (!Character::isSurrogate(c)) {
                if (dst.remaining() < 4)
                    return CoderResult::OVERFLOW;
                mark++;
                put(c, dst);
            } else if (Character::isHighSurrogate(c)) {
                if (!src.hasRemaining())
                    return CoderResult::UNDERFLOW;
                gchar low = src.get();
                if (Character::isLowSurrogate(low)) {
                    if (dst.remaining() < 4)
                        return CoderResult::OVERFLOW;
                    mark += 2;
                    put(Character::joinSurrogates(c, low), dst);
                } else {
                    errorLength = 1;
                    return CoderResult::MALFORMED;
                }
            } else {
                errorLength = 1;
                return CoderResult::MALFORMED;
            }
        }
        src.position(mark);
        return CoderResult::UNDERFLOW;
    } catch (...) {}
    src.position(mark);
    return Charset::CoderResult::UNDERFLOW;
}

gfloat UTF32::averageCharsPerByte() const {
    return 0.25f;
}

gfloat UTF32::averageBytesPerChar() const {
    return 4.0f;
}

CharBuffer UTF32::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer UTF32::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String UTF32::toString() const {
    return Charset::toString();
}

gbool UTF32::canEncode(gchar c) const {
    return Charset::canEncode(c);
}

gbool UTF32::contains(const Charset &cs) const {
    return Unicode::contains(cs);
}

Object &UTF32::clone() const {
    return INSTANCE;
}
