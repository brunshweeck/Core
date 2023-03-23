//
// Created by brunshweeck on 05/03/2023.
//

#include "ISO8859_1.h"
#include "../String.h"
#include "../Character.h"

ISO8859_1 ISO8859_1::INSTANCE{};

String ISO8859_1::name() const {
    return "ISO-8859-1";
}

Charset::CoderResult ISO8859_1::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
    int mark = src.position();
    try {
        while (src.hasRemaining()) {
            gbyte b = src.get();
            if (!dst.hasRemaining())
                return CoderResult::OVERFLOW;
            dst.put((char) (b & 0xff));
            mark++;
        }
        src.position(mark);
        return CoderResult::UNDERFLOW;
    } catch (...) {}
    src.position(mark);
    return CoderResult::UNDERFLOW;
}

Charset::CoderResult ISO8859_1::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    int mark = src.position();
    try {
        while (src.hasRemaining()) {
            gchar c = src.get();
            if (c <= u'\u00FF') {
                if (!dst.hasRemaining())
                    return CoderResult::OVERFLOW;
                dst.put((gbyte) c);
                mark++;
                continue;
            }
            if (Character::isHighSurrogate(c)){
                if(src.hasRemaining()){
                    CODING_ERROR_LENGTH = 1;
                    return CoderResult::MALFORMED;
                }
                gchar d = src.get();
                if (Character::isLowSurrogate(d)){
                    CODING_ERROR_LENGTH = 2;
                    return CoderResult::UNMAPPABLE;
                }
                CODING_ERROR_LENGTH = 1;
                return CoderResult::MALFORMED;
            }
            CODING_ERROR_LENGTH = 1;
            return CoderResult::MALFORMED;
        }
        return CoderResult::UNDERFLOW;
    } catch (...) {
        src.position(mark);
    }
    return CoderResult::UNDERFLOW;
}

gfloat ISO8859_1::averageCharsPerByte() const {
    return 1.0f;
}

gfloat ISO8859_1::averageBytesPerChar() const {
    return 1.0f;
}

gbool ISO8859_1::contains(const Charset &cs) const {
    return dynamic_cast<ISO8859_1 const *>(&cs);
}

Object &ISO8859_1::clone() const {
    return INSTANCE;
}

