//
// Created by brunshweeck on 27/02/2023.
//

#include "UTF16.h"
#include "../String.h"
#include "../Errors/OverflowError.h"

UTF16::UTF16(Endian byteOrder) : UTF16(byteOrder, false) {}

UTF16 UTF16::INSTANCE{};
UTF16 UTF16::BIG_INSTANCE{BIG};
UTF16 UTF16::LITTLE_INSTANCE{LITTLE};
UTF16 UTF16::BIG_BOM_INSTANCE{BIG, true};
UTF16 UTF16::LITTLE_BOM_INSTANCE{LITTLE, true};

Unicode::Endian UTF16::byteOrder() const {
    return _byteOrder == BIG || _byteOrder == LITTLE ? _byteOrder : NONE;
}

gchar UTF16::decode(int b1, int b2) const {
    if (currentByteOrder() == BIG)
        return (gchar) ((b1 << 8) | b2);
    else
        return (gchar) ((b2 << 8) | b1);
}

UTF16::UTF16(Unicode::Endian byteOrder, gbool withBOM) :
        Unicode(
                byteOrder == LITTLE ?
                withBOM ? u"UTF-16LE BOM" : u"UTF-16LE" :
                byteOrder == BIG ?
                withBOM ? u"UTF-16BE BOM" : u"UTF-16BE" :
                withBOM ? u"UTF-16 BOM" : u"UTF-16"
        ),
        _byteOrder(byteOrder), _withBOM(withBOM), _current(byteOrder) {
    if (_byteOrder == BIG) {
        encoderReplacement[0] = (gbyte) 0xff;
        encoderReplacement[1] = (gbyte) 0xfd;
        encoderReplacement[2] = (gbyte) 0;
        encoderReplacement[3] = (gbyte) 0;
        encoderReplacement[4] = (gbyte) 0;
    } else {
        encoderReplacement[0] = (gbyte) 0xfd;
        encoderReplacement[1] = (gbyte) 0xff;
        encoderReplacement[2] = (gbyte) 0;
        encoderReplacement[3] = (gbyte) 0;
        encoderReplacement[4] = (gbyte) 0;
    }
}

gbool UTF16::needsMark() const {
    return _withBOM;
}

String UTF16::name() const {
    return _byteOrder == LITTLE ?
           _withBOM ? "UTF-16LE BOM" : "UTF-16LE" :
           _byteOrder == BIG ?
           _withBOM ? "UTF-16BE BOM" : "UTF-16BE" :
           _withBOM ? "UTF-16 BOM" : "UTF-16";
}

gfloat UTF16::averageCharsPerByte() const {
    return 0.5;
}

gfloat UTF16::averageBytesPerChar() const {
    return 2;
}

Unicode::Endian UTF16::currentByteOrder() const {
    return _current == BIG || _current == LITTLE ? _current : NONE;
}

Charset::CoderResult UTF16::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
    gint mark = src.position();
    try {
        while (src.remaining() > 1) {
            gint b1 = src.get() & 0xFF;
            gint b2 = src.get() & 0xFF;
            if (byteOrder() == NONE) {
                gchar c = (gchar) ((b1 << 8) | b2);
                if (c == UTF16BE_BOM) {
                    _current = BIG;
                    mark += 2;
                    continue;
                } else if (c == UTF16LE_BOM) {
                    _current = LITTLE;
                    mark += 2;
                    continue;
                } else {
                    _current = BIG;
                }
            }
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
    } catch (OverflowError const &) {}
    src.position(mark);
    return Charset::CoderResult::UNDERFLOW;
}

void UTF16::reset() {
    _current = _byteOrder;
}

void UTF16::put(gchar c, ByteBuffer dst) {
    if (_byteOrder == BIG) {
        dst.put((gbyte) (c >> 8));
        dst.put((gbyte) (c & 0xff));
    } else {
        dst.put((gbyte) (c & 0xff));
        dst.put((gbyte) (c >> 8));
    }
}

Charset::CoderResult UTF16::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    int mark = src.position();
    gbool _needsMark = needsMark();

    if (needsMark() && src.hasRemaining()) {
        if (dst.remaining() < 2)
            return CoderResult::OVERFLOW;
        put(UTF16LE_BOM, dst);
        _needsMark = false;
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
            CoderResult cr = Charset::CoderResult::UNDERFLOW;
            gint uc = 0;
            if (Character::isHighSurrogate(c)) {
                if (!src.hasRemaining()) {
                    cr = Charset::CoderResult::UNDERFLOW;
                    uc = -1;
                } else {
                    gchar d = src.get();
                    if (Character::isLowSurrogate(c)) {
                        uc = Character::joinSurrogates(c, d);
                        cr = Charset::CoderResult::NONE;
                    } else
                        uc = -1;
                }
            } else if (Character::isLowSurrogate(c)) {
                uc = -1;
                errorLength = 1;
                cr = Charset::CoderResult::MALFORMED;
            } else {
                uc = c;
                cr = Charset::CoderResult::NONE;
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

Object &UTF16::clone() const {
    switch (_byteOrder) {
        case NONE: {
            static UTF16 utf16 = UTF16();
            return utf16;
        }
        case BIG: {
            if (_withBOM) {
                static UTF16 utf16BE_BOM = UTF16(BIG, true);
                return utf16BE_BOM;
            } else {
                static UTF16 utf16BE = UTF16(BIG);
                return utf16BE;
            }
        }
        case LITTLE: {
            if (_withBOM) {
                static UTF16 utf16LE_BOM = UTF16(LITTLE, true);
                return utf16LE_BOM;
            } else {
                static UTF16 utf16LE = UTF16(LITTLE);
                return utf16LE;
            }
        }
    }
}

CharBuffer UTF16::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer UTF16::encode(CharBuffer &in) {
    return Charset::encode(in);
}
