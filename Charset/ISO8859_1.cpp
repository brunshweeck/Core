//
// Created by brunshweeck on 05/03/2023.
//

#include "ISO8859_1.h"
#include "../String.h"

ISO8859_1::ISO8859_1() : Charset("ISO-8859-1") {}

ISO8859_1 ISO8859_1::INSTANCE{};

String ISO8859_1::name() const {
    return "ISO-8859-1";
}

Charset::ErrorAction ISO8859_1::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction ISO8859_1::unmappableAction() const {
    return Charset::unmappableAction();
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
                    errorLength = 1;
                    return CoderResult::MALFORMED;
                }
                gchar d = src.get();
                if (Character::isLowSurrogate(d)){
                    errorLength = 2;
                    return CoderResult::UNMAPPABLE;
                }
                errorLength = 1;
                return CoderResult::MALFORMED;
            }
            errorLength = 1;
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

CharBuffer ISO8859_1::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer ISO8859_1::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String ISO8859_1::toString() const {
    return Charset::toString();
}

gbool ISO8859_1::contains(const Charset &cs) const {
    return dynamic_cast<ISO8859_1 const *>(&cs);
}

gbool ISO8859_1::canEncode(gchar c) const {
    return Charset::canEncode(c);
}

Object &ISO8859_1::clone() const {
    return INSTANCE;
}

