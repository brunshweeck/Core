//
// Created by brunshweeck on 04/03/2023.
//

#include "US_ASCII.h"
#include "../Character.h"

US_ASCII US_ASCII::INSTANCE{};

String US_ASCII::name() const {
    return "US-ASCII";
}

Charset::CoderResult US_ASCII::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
    int mark = src.position();
    try {
        while (src.hasRemaining()) {
            gbyte b = src.get();
            if (b >= 0) {
                if (!dst.hasRemaining())
                    return CoderResult::OVERFLOW;
                dst.put((gchar) b);
                mark++;
                continue;
            }
            CODING_ERROR_LENGTH = 1;
            return CoderResult::MALFORMED;
        }
        src.position(mark);
        return CoderResult::UNDERFLOW;
    } catch (...) {}
    src.position(mark);
    return CoderResult::UNDERFLOW;
}

Charset::CoderResult US_ASCII::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    int mark = src.position();
    try {
        while (src.hasRemaining()) {
            gchar c = src.get();
            if (c < 0x80) {
                if (!dst.hasRemaining())
                    return CoderResult::OVERFLOW;
                dst.put((gbyte) c);
                mark++;
                continue;
            }
            if (Character::isSurrogate(c)) {
                if (Character::isHighSurrogate(c)) {
                    if (!src.hasRemaining()) {
                        CODING_ERROR_LENGTH = 1;
                        return CoderResult::UNDERFLOW;
                    }
                    gchar d = src.get();
                    if (Character::isLowSurrogate(d)) {
                        CODING_ERROR_LENGTH = 2;
                        return CoderResult::UNMAPPABLE;
                    }
                    CODING_ERROR_LENGTH = 1;
                    return CoderResult::MALFORMED;
                } else {
                    CODING_ERROR_LENGTH = 1;
                    return CoderResult::MALFORMED;
                }
            }
            CODING_ERROR_LENGTH = 1;
            return CoderResult::UNMAPPABLE;
        }
        src.position(mark);
        return CoderResult::UNDERFLOW;
    } catch (...) {}
    src.position(mark);
    return CoderResult::UNDERFLOW;
}

gfloat US_ASCII::averageCharsPerByte() const {
    return 1.0f;
}

gfloat US_ASCII::averageBytesPerChar() const {
    return 1.0f;
}

gbool US_ASCII::contains(const Charset &cs) const {
    return Class<US_ASCII>::hasInstance(cs);
}


Object &US_ASCII::clone() const {
    return INSTANCE;
}
