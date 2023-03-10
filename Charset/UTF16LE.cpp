//
// Created by brunshweeck on 04/03/2023.
//

#include "UTF16LE.h"
#include "../String.h"

UTF16LE::UTF16LE() : Unicode("UTF-16LE") {
    encoderReplacement[0] = (gbyte) 0xfd;
    encoderReplacement[1] = (gbyte) 0xff;
    encoderReplacement[2] = (gbyte) 0;
    encoderReplacement[3] = (gbyte) 0;
    encoderReplacement[4] = (gbyte) 0;
}

UTF16LE UTF16LE::INSTANCE{};

String UTF16LE::name() const {
    return "UTF-16LE";
}

Charset::ErrorAction UTF16LE::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction UTF16LE::unmappableAction() const {
    return Charset::unmappableAction();
}

Charset::CoderResult UTF16LE::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
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

void UTF16LE::put(gchar c, ByteBuffer dst) {
    dst.put((gbyte) (c & 0xff));
    dst.put((gbyte) (c >> 8));
}

Charset::CoderResult UTF16LE::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
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
            CoderResult cr;
            gint uc;
            if (Character::isHighSurrogate(c)) {
                if (!src.hasRemaining()) {
                    cr = Charset::CoderResult::UNDERFLOW;
                    uc = -1;
                } else {
                    gchar d = src.get();
                    if (Character::isLowSurrogate(c)) {
                        uc = Character::joinSurrogates(c, d);
                        cr = Charset::CoderResult::UNDERFLOW;
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

gfloat UTF16LE::averageCharsPerByte() const {
    return 0.5;
}

gfloat UTF16LE::averageBytesPerChar() const {
    return 2;
}

CharBuffer UTF16LE::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer UTF16LE::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String UTF16LE::toString() const {
    return Charset::toString();
}

Object &UTF16LE::clone() const {
    return INSTANCE;
}

gchar UTF16LE::decode(gint b1, gint b2) {
    return (gchar) ((b2 << 8) | b1);
}

