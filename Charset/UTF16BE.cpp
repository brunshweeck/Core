//
// Created by brunshweeck on 04/03/2023.
//

#include "UTF16BE.h"
#include "../String.h"
#include "../Errors/OverflowError.h"

UTF16BE::UTF16BE(): Unicode("UTF-16BE") {
    encoderReplacement[0] = (gbyte) 0xff;
    encoderReplacement[1] = (gbyte) 0xfd;
    encoderReplacement[2] = (gbyte) 0;
    encoderReplacement[3] = (gbyte) 0;
    encoderReplacement[4] = (gbyte) 0;
}

UTF16BE UTF16BE::INSTANCE{};

String UTF16BE::name() const {
    return "UTF-16BE";
}

Charset::ErrorAction UTF16BE::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction UTF16BE::unmappableAction() const {
    return Charset::unmappableAction();
}

Charset::CoderResult UTF16BE::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
    gint mark = src.position();
    try {
        while (src.remaining() > 1) {
            gint b1 = src.get() & 0xFF;
            gint b2 = src.get() & 0xFF;
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
    } catch (...) {}
    src.position(mark);
    return Charset::CoderResult::UNDERFLOW;
}

Charset::CoderResult UTF16BE::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    gint mark = src.position();
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
            CoderResult cr;
            gint uc;
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

gfloat UTF16BE::averageCharsPerByte() const {
    return 0.5f;
}

gfloat UTF16BE::averageBytesPerChar() const {
    return 2;
}

CharBuffer UTF16BE::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer UTF16BE::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String UTF16BE::toString() const {
    return Charset::toString();
}

gbool UTF16BE::contains(const Charset &cs) const {
    return Unicode::contains(cs);
}

Object &UTF16BE::clone() const {
    return INSTANCE;
}

void UTF16BE::put(gchar c, ByteBuffer dst) {
    dst.put((gbyte) (c >> 8));
    dst.put((gbyte) (c & 0xff));
}

gchar UTF16BE::decode(gint b1, gint b2) {
    return (gchar) ((b1 << 8) | b2);
}

