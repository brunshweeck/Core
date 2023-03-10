//
// Created by brunshweeck on 05/03/2023.
//

#include "ISO8859_7.h"
#include "../String.h"
#include "../extern/SingleByte.h"

static gchar b2c[] = u""
                     "\u0080\u0081\u0082\u0083\u0084\u0085\u0086\u0087"       // 0x80 - 0x87
                     "\u0088\u0089\u008A\u008B\u008C\u008D\u008E\u008F"       // 0x88 - 0x8f
                     "\u0090\u0091\u0092\u0093\u0094\u0095\u0096\u0097"       // 0x90 - 0x97
                     "\u0098\u0099\u009A\u009B\u009C\u009D\u009E\u009F"       // 0x98 - 0x9f
                     "\u00A0\u2018\u2019\u00A3\u20AC\u20AF\u00A6\u00A7"       // 0xa0 - 0xa7
                     "\u00A8\u00A9\u037A\u00AB\u00AC\u00AD\uFFFD\u2015"       // 0xa8 - 0xaf
                     "\u00B0\u00B1\u00B2\u00B3\u0384\u0385\u0386\u00B7"       // 0xb0 - 0xb7
                     "\u0388\u0389\u038A\u00BB\u038C\u00BD\u038E\u038F"       // 0xb8 - 0xbf
                     "\u0390\u0391\u0392\u0393\u0394\u0395\u0396\u0397"       // 0xc0 - 0xc7
                     "\u0398\u0399\u039A\u039B\u039C\u039D\u039E\u039F"       // 0xc8 - 0xcf
                     "\u03A0\u03A1\uFFFD\u03A3\u03A4\u03A5\u03A6\u03A7"       // 0xd0 - 0xd7
                     "\u03A8\u03A9\u03AA\u03AB\u03AC\u03AD\u03AE\u03AF"       // 0xd8 - 0xdf
                     "\u03B0\u03B1\u03B2\u03B3\u03B4\u03B5\u03B6\u03B7"       // 0xe0 - 0xe7
                     "\u03B8\u03B9\u03BA\u03BB\u03BC\u03BD\u03BE\u03BF"       // 0xe8 - 0xef
                     "\u03C0\u03C1\u03C2\u03C3\u03C4\u03C5\u03C6\u03C7"       // 0xf0 - 0xf7
                     "\u03C8\u03C9\u03CA\u03CB\u03CC\u03CD\u03CE\uFFFD"       // 0xf8 - 0xff
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

static gint _ = SingleByte<256, 0, 0x400 - 1, 0x100 - 1>::initC2B(b2c, c2bNR, c2b, c2bIndex);


ISO8859_7::ISO8859_7() : Charset("ISO-8859-7") {}

ISO8859_7 ISO8859_7::INSTANCE{};

String ISO8859_7::name() const {
    return "ISO-8859-7";
}

Charset::ErrorAction ISO8859_7::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction ISO8859_7::unmappableAction() const {
    return Charset::unmappableAction();
}

Charset::CoderResult ISO8859_7::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
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

Charset::CoderResult ISO8859_7::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
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

gfloat ISO8859_7::averageCharsPerByte() const {
    return 1.0f;
}

gfloat ISO8859_7::averageBytesPerChar() const {
    return 1.0f;
}

CharBuffer ISO8859_7::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer ISO8859_7::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String ISO8859_7::toString() const {
    return Charset::toString();
}

gbool ISO8859_7::contains(const Charset &cs) const {
    return dynamic_cast<ISO8859_7 const *>(&cs);
}

gbool ISO8859_7::canEncode(gchar c) const {
    return Charset::canEncode(c);
}

Object &ISO8859_7::clone() const {
    return INSTANCE;
}


