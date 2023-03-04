//
// Created by brunshweeck on 28/02/2023.
//

#include "UTF32.h"
#include "../String.h"

UTF32::UTF32(Unicode::Endian byteOrder) : UTF32(byteOrder, false) {}

UTF32 UTF32::INSTANCE{};
UTF32 UTF32::BIG_INSTANCE{BIG};
UTF32 UTF32::LITTLE_INSTANCE{LITTLE};
UTF32 UTF32::BIG_BOM_INSTANCE{BIG, true};
UTF32 UTF32::LITTLE_BOM_INSTANCE{LITTLE, true};

UTF32::UTF32(Unicode::Endian byteOrder, gbool withBOM) :
        Unicode(
                byteOrder == LITTLE ?
                withBOM ? u"UTF-32LE BOM" : u"UTF-32LE" :
                byteOrder == BIG ?
                withBOM ? u"UTF-32BE BOM" : u"UTF-32BE" :
                withBOM ? u"UTF-32 BOM" : u"UTF-32"
        ),
        _byteOrder(byteOrder), _withBOM(withBOM), _current(byteOrder) {
    if (_byteOrder == BIG) {
        encoderReplacement[0] = (gbyte) 0;
        encoderReplacement[1] = (gbyte) 0;
        encoderReplacement[2] = (gbyte) 0xff;
        encoderReplacement[3] = (gbyte) 0xfd;
        encoderReplacement[4] = (gbyte) 0;
    } else {
        encoderReplacement[0] = (gbyte) 0xfd;
        encoderReplacement[1] = (gbyte) 0xff;
        encoderReplacement[2] = (gbyte) 0;
        encoderReplacement[3] = (gbyte) 0;
        encoderReplacement[4] = (gbyte) 0;
    }
}

Unicode::Endian UTF32::byteOrder() const {
    return _byteOrder;
}

Unicode::Endian UTF32::currentByteOrder() const {
    return _current;
}

gbool UTF32::needsMark() const {
    return _withBOM;
}

String UTF32::name() const {
    return _byteOrder == LITTLE ?
           _withBOM ? "UTF-32LE BOM" : "UTF-32LE" :
           _byteOrder == BIG ?
           _withBOM ? "UTF-32BE BOM" : "UTF-32BE" :
           _withBOM ? "UTF-32 BOM" : "UTF-32";
}

gfloat UTF32::averageCharsPerByte() const {
    return 0.25f;
}

gfloat UTF32::averageBytesPerChar() const {
    return 4;
}

gint UTF32::get(ByteBuffer &src) {
    return (_current == BIG)
           ? (((src.get() & 0xff) << 24) |
              ((src.get() & 0xff) << 16) |
              ((src.get() & 0xff) << 8) |
              (src.get() & 0xff))
           : ((src.get() & 0xff) |
              ((src.get() & 0xff) << 8) |
              ((src.get() & 0xff) << 16) |
              ((src.get() & 0xff) << 24));
}

Charset::CoderResult UTF32::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
    if (src.remaining() < 4)
        return CoderResult::UNDERFLOW;
    gint mark = src.position();
    gint cp;
    try {
        if (_current == NONE) {
            cp = ((src.get() & 0xff) << 24) |
                 ((src.get() & 0xff) << 16) |
                 ((src.get() & 0xff) << 8) |
                 (src.get() & 0xff);
            if (cp == UTF32BE_BOM && _byteOrder != LITTLE) {
                _current = BIG;
                mark += 4;
            } else if (cp == UTF32LE_BOM && _byteOrder != BIG) {
                _current = LITTLE;
                mark += 4;
            } else {
                if (_byteOrder == NONE)
                    _current = BIG;
                else
                    _current = _byteOrder;
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
    if (_withBOM && src.hasRemaining()) {
        if (dst.remaining() < 4)
            return CoderResult::OVERFLOW;
        put(UTF32BE_BOM, dst);
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
                    errorLength = 1;
                    return CoderResult::MALFORMED;
                }
            } else {
                // assert Character.isLowSurrogate(c);
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

void UTF32::put(gint cp, ByteBuffer &dst) {
    if (_byteOrder == BIG) {
        dst.put((gbyte) (cp >> 24));
        dst.put((gbyte) (cp >> 16));
        dst.put((gbyte) (cp >> 8));
        dst.put((gbyte) cp);
    } else {
        dst.put((gbyte) cp);
        dst.put((gbyte) (cp >> 8));
        dst.put((gbyte) (cp >> 16));
        dst.put((gbyte) (cp >> 24));
    }
}

void UTF32::reset() {
    _current = _byteOrder;
}

Object &UTF32::clone() const {
    switch (_byteOrder) {
        case NONE: {
            static UTF32 utf32 = UTF32();
            return utf32;
        }
        case BIG: {
            if (_withBOM) {
                static UTF32 utf32BE_BOM = UTF32(BIG, true);
                return utf32BE_BOM;
            } else {
                static UTF32 utf32BE = UTF32(BIG);
                return utf32BE;
            }
        }
        case LITTLE: {
            if (_withBOM) {
                static UTF32 utf32LE_BOM = UTF32(LITTLE, true);
                return utf32LE_BOM;
            } else {
                static UTF32 utf32LE = UTF32(LITTLE);
                return utf32LE;
            }
        }
    }
}

CharBuffer UTF32::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer UTF32::encode(CharBuffer &in) {
    return Charset::encode(in);
}
