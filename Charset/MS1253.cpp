//
// Created by brunshweeck on 28/02/2023.
//

#include "MS1253.h"
#include "../String.h"

static gchar bytesToChar[] =
        u"\u20AC\uFFFD\u201A\u0192\u201E\u2026\u2020\u2021"       // 0x80 - 0x87
        "\uFFFD\u2030\uFFFD\u2039\uFFFD\uFFFD\uFFFD\uFFFD"       // 0x88 - 0x8f
        "\uFFFD\u2018\u2019\u201C\u201D\u2022\u2013\u2014"       // 0x90 - 0x97
        "\uFFFD\u2122\uFFFD\u203A\uFFFD\uFFFD\uFFFD\uFFFD"       // 0x98 - 0x9f
        "\u00A0\u0385\u0386\u00A3\u00A4\u00A5\u00A6\u00A7"       // 0xa0 - 0xa7
        "\u00A8\u00A9\uFFFD\u00AB\u00AC\u00AD\u00AE\u2015"       // 0xa8 - 0xaf
        "\u00B0\u00B1\u00B2\u00B3\u0384\u00B5\u00B6\u00B7"       // 0xb0 - 0xb7
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
static gchar charToBytes[0x600] = u"";
static gchar charToBytes_indexes[0x100] = u"";
static gchar charToBytes_NR[0] = {};
static CORE_FAST gchar UNMAPPABLE_DECODING = 0xFFFD;
static CORE_FAST gint UNMAPPABLE_ENCODING = 0xFFFD;

static gint initC2B() {
    for (char16_t & charToBytes_index : charToBytes_indexes)
        charToBytes_index = 0xFFFD;
    for (char16_t & charToByte : charToBytes)
        charToByte = 0xFFFD;
    gint off = 0;
    for (gint i = 0; i < sizeof(bytesToChar) / 2; i++) {
        gchar c = bytesToChar[i];
        if (c == 0xFFFD)
            continue;
        gint index = (c >> 8);
        if (charToBytes_indexes[index] == 0xFFFD) {
            charToBytes_indexes[index] = (gchar) off;
            off += 0x100;
        }
        index = charToBytes_indexes[index] + (c & 0xff);
        charToBytes[index] = (gchar) ((i >= 0x80) ? (i - 0x80) : (i + 0x80));
    }
    return 0;
}

static gint _ = initC2B();

MS1253::MS1253() : Charset("Windows-1251") {}

String MS1253::name() const {
    return "Windows-1251";
}

gchar MS1253::decode(gint b) {
    return bytesToChar[b + 128];
}

Charset::CoderResult MS1253::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
    gint mark = src.position();
    try {
        while (src.hasRemaining()) {
            gchar c = decode(src.get());
            if (c == UNMAPPABLE_DECODING) {
                errorLength = 1;
                return Charset::CoderResult::UNMAPPABLE;
            }
            if (!dst.hasRemaining())
                return Charset::CoderResult::OVERFLOW;
            dst.put(c);
            mark++;
        }
        src.position(mark);
        return Charset::CoderResult::UNDERFLOW;
    } catch (...) {}
    src.position(mark);
    return CoderResult::UNDERFLOW;
}

Charset::CoderResult MS1253::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    gint mark = src.position();
    try {
        while (src.hasRemaining()) {
            gchar c = src.get();
            gint b = encode(c);
            if (b == UNMAPPABLE_ENCODING) {
                if (Character::isSurrogate(c)) {
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
                    errorLength = uc > 0xFFFF ? 2 : 1;
                    return Charset::CoderResult::UNMAPPABLE;
                }
                errorLength = 1;
                return CoderResult::UNMAPPABLE;
            }
            if (!dst.hasRemaining())
                return CoderResult::OVERFLOW;
            dst.put((gbyte) b);
            mark++;
        }
        src.position(mark);
        return CoderResult::UNDERFLOW;
    } catch (...) {}
    src.position(mark);
    return CoderResult::UNDERFLOW;
}

gfloat MS1253::averageCharsPerByte() const {
    return 1;
}

gfloat MS1253::averageBytesPerChar() const {
    return 1;
}

gbool MS1253::contains(const Charset &cs) const {
    return dynamic_cast<MS1253 const *>(&cs) || name().equals("US-ASCII");
}

Object &MS1253::clone() const {
    static MS1253 ms1253 = MS1253();
    return ms1253;
}

gint MS1253::encode(gchar ch) {
    gchar index = charToBytes_indexes[ch >> 8];
    if (index == UNMAPPABLE_ENCODING)
        return UNMAPPABLE_ENCODING;
    return charToBytes[index + (ch & 0xff)];
}

