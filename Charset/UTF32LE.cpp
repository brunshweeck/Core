//
// Created by brunshweeck on 04/03/2023.
//

#include "UTF32LE.h"
#include "../String.h"

UTF32LE::UTF32LE(): Unicode("UTF-32LE") {
    encoderReplacement[0] = (gbyte) 0xfd;
    encoderReplacement[1] = (gbyte) 0xff;
    encoderReplacement[2] = (gbyte) 0;
    encoderReplacement[3] = (gbyte) 0;
    encoderReplacement[4] = (gbyte) 0;
}

UTF32LE UTF32LE::INSTANCE{};

String UTF32LE::name() const {
    return "UTF-32LE";
}

Charset::ErrorAction UTF32LE::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction UTF32LE::unmappableAction() const {
    return Charset::unmappableAction();
}

Charset::CoderResult UTF32LE::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
    if (src.remaining() < 4)
        return CoderResult::UNDERFLOW;
    gint mark = src.position();
    gint cp;
    try {
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

Charset::CoderResult UTF32LE::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
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

gfloat UTF32LE::averageCharsPerByte() const {
    return 0.25;
}

gfloat UTF32LE::averageBytesPerChar() const {
    return 4.0f;
}

CharBuffer UTF32LE::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer UTF32LE::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String UTF32LE::toString() const {
    return Charset::toString();
}

gbool UTF32LE::canEncode(gchar c) const {
    return Charset::canEncode(c);
}

gbool UTF32LE::contains(const Charset &cs) const {
    return Unicode::contains(cs);
}

Object &UTF32LE::clone() const {
    return INSTANCE;
}

gint UTF32LE::get(ByteBuffer &src) {
    return (src.get() & 0xff) |
           (src.get() & 0xff) << 8 |
           (src.get() & 0xff) << 16 |
           (src.get() & 0xff) << 24;
}

void UTF32LE::put(gint cp, ByteBuffer &dst) {
    dst.put((gbyte) cp);
    dst.put((gbyte) (cp >> 8));
    dst.put((gbyte) (cp >> 16));
    dst.put((gbyte) (cp >> 24));
}