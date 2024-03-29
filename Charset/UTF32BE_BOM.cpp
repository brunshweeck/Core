//
// Created by brunshweeck on 04/03/2023.
//

#include "UTF32BE_BOM.h"
#include "../String.h"
#include "../Character.h"


UTF32BE_BOM UTF32BE_BOM::INSTANCE{};

String UTF32BE_BOM::name() const {
    return "UTF-32-BOM";
}

Charset::CoderResult UTF32BE_BOM::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
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
                CODING_ERROR_LENGTH = 4;
                return CoderResult::MALFORMED;
            }
        }
        src.position(mark);
        return CoderResult::UNDERFLOW;
    } catch (...) {}
    src.position(mark);
    return Charset::CoderResult::UNDERFLOW;
}

Charset::CoderResult UTF32BE_BOM::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    gint mark = src.position();
    if (src.hasRemaining()) {
        if (dst.remaining() < 4)
            return CoderResult::OVERFLOW;
        put(BYTE_ORDER_MASK, dst);
    }
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
                    CODING_ERROR_LENGTH = 1;
                    return CoderResult::MALFORMED;
                }
            } else {
                CODING_ERROR_LENGTH = 1;
                return CoderResult::MALFORMED;
            }
        }
        src.position(mark);
        return CoderResult::UNDERFLOW;
    } catch (...) {}
    src.position(mark);
    return Charset::CoderResult::UNDERFLOW;
}

gfloat UTF32BE_BOM::averageCharsPerByte() const {
    return 0.25f;
}

gfloat UTF32BE_BOM::averageBytesPerChar() const {
    return 4.0f;
}

Object &UTF32BE_BOM::clone() const {
    return INSTANCE;
}

gint UTF32BE_BOM::get(ByteBuffer &src) {
    return (src.get() & 0xff) << 24 |
           (src.get() & 0xff) << 16 |
           (src.get() & 0xff) << 8 |
           (src.get() & 0xff);
}

void UTF32BE_BOM::put(gint cp, ByteBuffer &dst) {
    dst.put((gbyte) (cp >> 24));
    dst.put((gbyte) (cp >> 16));
    dst.put((gbyte) (cp >> 8));
    dst.put((gbyte) cp);
}
