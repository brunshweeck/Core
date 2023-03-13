//
// Created by brunshweeck on 05/03/2023.
//

#include "ISO8859_9.h"
#include "../String.h"
#include "../extern/SingleByte.h"
#include "../Character.h"
static gchar b2c[] = u""
                     "\u0080\u0081\u0082\u0083\u0084\u0085\u0086\u0087"       // 0x80 - 0x87
                     "\u0088\u0089\u008A\u008B\u008C\u008D\u008E\u008F"       // 0x88 - 0x8f
                     "\u0090\u0091\u0092\u0093\u0094\u0095\u0096\u0097"       // 0x90 - 0x97
                     "\u0098\u0099\u009A\u009B\u009C\u009D\u009E\u009F"       // 0x98 - 0x9f
                     "\u00A0\u00A1\u00A2\u00A3\u00A4\u00A5\u00A6\u00A7"       // 0xa0 - 0xa7
                     "\u00A8\u00A9\u00AA\u00AB\u00AC\u00AD\u00AE\u00AF"       // 0xa8 - 0xaf
                     "\u00B0\u00B1\u00B2\u00B3\u00B4\u00B5\u00B6\u00B7"       // 0xb0 - 0xb7
                     "\u00B8\u00B9\u00BA\u00BB\u00BC\u00BD\u00BE\u00BF"       // 0xb8 - 0xbf
                     "\u00C0\u00C1\u00C2\u00C3\u00C4\u00C5\u00C6\u00C7"       // 0xc0 - 0xc7
                     "\u00C8\u00C9\u00CA\u00CB\u00CC\u00CD\u00CE\u00CF"       // 0xc8 - 0xcf
                     "\u011E\u00D1\u00D2\u00D3\u00D4\u00D5\u00D6\u00D7"       // 0xd0 - 0xd7
                     "\u00D8\u00D9\u00DA\u00DB\u00DC\u0130\u015E\u00DF"       // 0xd8 - 0xdf
                     "\u00E0\u00E1\u00E2\u00E3\u00E4\u00E5\u00E6\u00E7"       // 0xe0 - 0xe7
                     "\u00E8\u00E9\u00EA\u00EB\u00EC\u00ED\u00EE\u00EF"       // 0xe8 - 0xef
                     "\u011F\u00F1\u00F2\u00F3\u00F4\u00F5\u00F6\u00F7"       // 0xf0 - 0xf7
                     "\u00F8\u00F9\u00FA\u00FB\u00FC\u0131\u015F\u00FF"       // 0xf8 - 0xff
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
static gchar c2b[0x200] = u"";
static gchar c2bIndex[0x100] = u"";
static gchar c2bNR[] = u"";
CORE_FAST static gchar UNMAPPABLE_DECODING = u'\ufffd';
CORE_FAST static gint UNMAPPABLE_ENCODING = 0xfffd;
static gbool isAsciiCompatible = true;
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

static gint _ = SingleByte<256, 0, 0x200 - 1, 0x100 - 1>::initC2B(b2c, c2bNR, c2b, c2bIndex);


ISO8859_9::ISO8859_9() : Charset("ISO-8859-9") {}

ISO8859_9 ISO8859_9::INSTANCE{};

String ISO8859_9::name() const {
    return "ISO-8859-9";
}

Charset::ErrorAction ISO8859_9::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction ISO8859_9::unmappableAction() const {
    return Charset::unmappableAction();
}

Charset::CoderResult ISO8859_9::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
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

Charset::CoderResult ISO8859_9::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    struct Surrogate {
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

gfloat ISO8859_9::averageCharsPerByte() const {
    return 1.0f;
}

gfloat ISO8859_9::averageBytesPerChar() const {
    return 1.0f;
}

CharBuffer ISO8859_9::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer ISO8859_9::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String ISO8859_9::toString() const {
    return Charset::toString();
}

gbool ISO8859_9::contains(const Charset &cs) const {
    return dynamic_cast<ISO8859_9 const *>(&cs);
}

gbool ISO8859_9::canEncode(gchar c) const {
    return Charset::canEncode(c);
}

Object &ISO8859_9::clone() const {
    return INSTANCE;
}


