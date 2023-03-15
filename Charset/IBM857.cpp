//
// Created by brunshweeck on 05/03/2023.
//

#include "IBM857.h"
#include "../String.h"
#include "../extern/SingleByte.h"
#include "../Character.h"
static gchar b2c[] = u""
                     "\u00C7\u00FC\u00E9\u00E2\u00E4\u00E0\u00E5\u00E7"       // 0x80 - 0x87
                     "\u00EA\u00EB\u00E8\u00EF\u00EE\u0131\u00C4\u00C5"       // 0x88 - 0x8f
                     "\u00C9\u00E6\u00C6\u00F4\u00F6\u00F2\u00FB\u00F9"       // 0x90 - 0x97
                     "\u0130\u00D6\u00DC\u00F8\u00A3\u00D8\u015E\u015F"       // 0x98 - 0x9f
                     "\u00E1\u00ED\u00F3\u00FA\u00F1\u00D1\u011E\u011F"       // 0xa0 - 0xa7
                     "\u00BF\u00AE\u00AC\u00BD\u00BC\u00A1\u00AB\u00BB"       // 0xa8 - 0xaf
                     "\u2591\u2592\u2593\u2502\u2524\u00C1\u00C2\u00C0"       // 0xb0 - 0xb7
                     "\u00A9\u2563\u2551\u2557\u255D\u00A2\u00A5\u2510"       // 0xb8 - 0xbf
                     "\u2514\u2534\u252C\u251C\u2500\u253C\u00E3\u00C3"       // 0xc0 - 0xc7
                     "\u255A\u2554\u2569\u2566\u2560\u2550\u256C\u00A4"       // 0xc8 - 0xcf
                     "\u00BA\u00AA\u00CA\u00CB\u00C8\uFFFD\u00CD\u00CE"       // 0xd0 - 0xd7
                     "\u00CF\u2518\u250C\u2588\u2584\u00A6\u00CC\u2580"       // 0xd8 - 0xdf
                     "\u00D3\u00DF\u00D4\u00D2\u00F5\u00D5\u00B5\uFFFD"       // 0xe0 - 0xe7
                     "\u00D7\u00DA\u00DB\u00D9\u00EC\u00FF\u00AF\u00B4"       // 0xe8 - 0xef
                     "\u00AD\u00B1\uFFFD\u00BE\u00B6\u00A7\u00F7\u00B8"       // 0xf0 - 0xf7
                     "\u00B0\u00A8\u00B7\u00B9\u00B3\u00B2\u25A0\u00A0"       // 0xf8 - 0xff
                     "\u0000\u0001\u0002\u0003\u0004\u0005\u0006\u0007"       // 0x00 - 0x07
                     "\b\t\n\u000B\f\r\u000E\u000F"       // 0x08 - 0x0f
                     "\u0010\u0011\u0012\u0013\u0014\u0015\u0016\u0017"       // 0x10 - 0x17
                     "\u0018\u0019\u001A\u001B\u001C\u001D\u001E\u001F"       // 0x18 - 0x1f
                     "\u0020\u0021\"\u0023\u0024\u0025\u0026\'"       // 0x20 - 0x27
                     "\u0028\u0029\u002A\u002B\u002C\u002D\u002E\u002F"       // 0x28 - 0x2f
                     "\u0030\u0031\u0032\u0033\u0034\u0035\u0036\u0037"       // 0x30 - 0x37
                     "\u0038\u0039\u003A\u003B\u003C\u003D\u003E\u003F"       // 0x38 - 0x3f
                     "\u0040\u0041\u0042\u0043\u0044\u0045\u0046\u0047"       // 0x40 - 0x47
                     "\u0048\u0049\u004A\u004B\u004C\u004D\u004E\u004F"       // 0x48 - 0x4f
                     "\u0050\u0051\u0052\u0053\u0054\u0055\u0056\u0057"       // 0x50 - 0x57
                     "\u0058\u0059\u005A\u005B\\\u005D\u005E\u005F"       // 0x58 - 0x5f
                     "\u0060\u0061\u0062\u0063\u0064\u0065\u0066\u0067"       // 0x60 - 0x67
                     "\u0068\u0069\u006A\u006B\u006C\u006D\u006E\u006F"       // 0x68 - 0x6f
                     "\u0070\u0071\u0072\u0073\u0074\u0075\u0076\u0077"       // 0x70 - 0x77
                     "\u0078\u0079\u007A\u007B\u007C\u007D\u007E\u007F" ;      // 0x78 - 0x7f
static gchar c2b[0x400] = u"";
static gchar c2bIndex[0x100] = u"";
static gchar c2bNR[] = u"";
CORE_FAST static gchar UNMAPPABLE_DECODING = u'\ufffd';
CORE_FAST static gint UNMAPPABLE_ENCODING = 0xfffd;
static gbool isAsciiCompatible = false;
static gbool isLatinCompatible = false;

static gchar decode(gint b) {
    return b2c[b + 128];
}

static gint encode(gchar ch) {
    gchar index = c2bIndex[ch >> 8];
    if (index == UNMAPPABLE_ENCODING)
        return UNMAPPABLE_ENCODING;
    return c2b[index + (ch & 0xff)];
}

static gint _ = SingleByte<256, 0, 0x400 - 1, 0x100 - 1>::initC2B(b2c, c2bNR, c2b, c2bIndex);


IBM857::IBM857() : Charset("ISO-8859-2") {}

IBM857 IBM857::INSTANCE{};

String IBM857::name() const {
    return "ISO-8859-2";
}

Charset::ErrorAction IBM857::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction IBM857::unmappableAction() const {
    return Charset::unmappableAction();
}

Charset::CoderResult IBM857::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
    gint mark = src.position();
    try {
        while (src.hasRemaining()) {
            gchar c = ::decode(src.get());
            if (c == UNMAPPABLE_DECODING) {
                errorLength = 1;
                return CoderResult::MALFORMED;
            }
            if (!dst.hasRemaining())
                return CoderResult::OVERFLOW;
            dst.put(c);
            mark++;
        }
        return CoderResult::UNDERFLOW;
    } catch (...) {
        src.position(mark);
    }
    return CoderResult::UNDERFLOW;
}

Charset::CoderResult IBM857::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    struct Surrogate {
        CORE_IMPLICIT Surrogate(gint &errorLength) : errorLength(errorLength) {}
        gint& errorLength;
        gint isPair = false;
        Charset::CoderResult error = Charset::CoderResult::UNDERFLOW;
        gint character = 0;
        gint parse(gchar c, CharBuffer& in) {
            if (Character::isHighSurrogate(c)) {
                if (!in.hasRemaining()) {
                    error = Charset::CoderResult::UNDERFLOW;
                    return -1;
                }
                gchar d = in.get();
                if (Character::isLowSurrogate(d)) {
                    character = Character::joinSurrogates(c, d);
                    isPair = true;
                    return character;
                }
                errorLength = 1;
                error = Charset::CoderResult::MALFORMED;
                return -1;
            }
            if (Character::isLowSurrogate(c)) {
                errorLength = 1;
                error = Charset::CoderResult::MALFORMED;
                return -1;
            }
            character = c;
            isPair = false;
            return character;
        }
    };
    gint mark = src.position();
    Surrogate sgp = {errorLength};
    try {
        while (src.hasRemaining()) {
            gchar c = src.get();
            gint b = ::encode(c);
            if (b == UNMAPPABLE_ENCODING) {
                if (Character::isSurrogate(c)) {
                    if (sgp.parse(c, src) < 0)
                        return sgp.error;
                    return CoderResult::UNMAPPABLE;
                }
                errorLength = 1;
                return CoderResult::UNMAPPABLE;
            }
            if (!dst.hasRemaining())
                return CoderResult::OVERFLOW;
            dst.put((gbyte) b);
            mark++;
        }
        return CoderResult::UNDERFLOW;
    } catch (...) {
        src.position(mark);
    }
    return CoderResult::UNDERFLOW;
}

gfloat IBM857::averageCharsPerByte() const {
    return 1.0f;
}

gfloat IBM857::averageBytesPerChar() const {
    return 1.0f;
}

CharBuffer IBM857::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer IBM857::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String IBM857::toString() const {
    return Charset::toString();
}

gbool IBM857::contains(const Charset &cs) const {
    return dynamic_cast<IBM857 const *>(&cs);
}

gbool IBM857::canEncode(gchar c) const {
    return Charset::canEncode(c);
}

Object &IBM857::clone() const {
    return INSTANCE;
}

