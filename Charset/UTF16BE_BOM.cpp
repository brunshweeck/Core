//
// Created by brunshweeck on 04/03/2023.
//

#include "UTF16BE_BOM.h"
#include "../Character.h"


UTF16BE_BOM UTF16BE_BOM::INSTANCE{};

String UTF16BE_BOM::name() const {
    return "UTF-16BE-BOM";
}

Charset::CoderResult UTF16BE_BOM::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
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
                        CODING_ERROR_LENGTH = 4;
                        return CoderResult::MALFORMED;
                    }
                    if (dst.remaining() < 2)
                        return CoderResult::OVERFLOW;
                    mark += 4;
                    dst.put(c);
                    dst.put(c2);
                    continue;
                }
                CODING_ERROR_LENGTH = 2;
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

Charset::CoderResult UTF16BE_BOM::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    int mark = src.position();
    if (src.hasRemaining()) {
        if (dst.remaining() < 2)
            return CoderResult::OVERFLOW;
        put(BYTE_ORDER_MASK, dst);
    }
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
                        CODING_ERROR_LENGTH = 1;
                        cr = Charset::CoderResult::MALFORMED;
                    }
                }
            } else {
                uc = -1;
                CODING_ERROR_LENGTH = 1;
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

gfloat UTF16BE_BOM::averageCharsPerByte() const {
    return 0.5f;
}

gfloat UTF16BE_BOM::averageBytesPerChar() const {
    return 2.0f;
}

Object &UTF16BE_BOM::clone() const {
    return INSTANCE;
}

gchar UTF16BE_BOM::decode(int b1, int b2) {
    return (gchar) ((b1 << 8) | b2);
}

void UTF16BE_BOM::put(gchar c, ByteBuffer &dst) {
    dst.put((gbyte) (c >> 4));
    dst.put((gbyte) (c & 0xff));
}


