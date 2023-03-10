//
// Created by brunshweeck on 04/03/2023.
//

#include "US_ASCII.h"
#include "../String.h"

US_ASCII::US_ASCII() : Charset("US-ASCII") {}

US_ASCII US_ASCII::INSTANCE{};

String US_ASCII::name() const {
    return "US-ASCII";
}

Charset::ErrorAction US_ASCII::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction US_ASCII::unmappableAction() const {
    return Charset::unmappableAction();
}

static gint surrogate_parsing(gchar c, CharBuffer& in, gint& errorL, Charset::CoderResult& error) {
    gbool isPair = false;
    gint character = -1;
    if (Character::isHighSurrogate(c)) {
        if (!in.hasRemaining()) {
            error = Charset::CoderResult::UNDERFLOW;
            return -1;
        }
        gchar d = in.get();
        if (Character::isLowSurrogate(d)) {
            character = Character::joinSurrogates(c, d);
            isPair = true;
            error = Charset::CoderResult::UNDERFLOW;
            return character;
        }
        errorL = 1;
        error = Charset::CoderResult::MALFORMED;
        return -1;
    }
    if (Character::isLowSurrogate(c)) {
        errorL = 1;
        error = Charset::CoderResult::MALFORMED;
        return -1;
    }
    character = c;
    isPair = false;
    error = Charset::CoderResult::UNDERFLOW;
    return character;
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
            errorLength = 1;
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
                    if(!src.hasRemaining()){
                        errorLength = 1;
                        return CoderResult::UNDERFLOW;
                    }
                    gchar d = src.get();
                    if (Character::isLowSurrogate(d)){
                        errorLength = 2;
                        return CoderResult::UNMAPPABLE;
                    }
                    errorLength = 1;
                    return CoderResult::MALFORMED;
                } else {
                    errorLength = 1;
                    return CoderResult::MALFORMED;
                }
            }
            errorLength = 1;
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

CharBuffer US_ASCII::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer US_ASCII::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String US_ASCII::toString() const {
    return Charset::toString();
}

gbool US_ASCII::contains(const Charset &cs) const {
    return dynamic_cast<US_ASCII const *>(&cs);
}

gbool US_ASCII::canEncode(gchar c) const {
    return Charset::canEncode(c);
}

Object &US_ASCII::clone() const {
    return INSTANCE;
}
