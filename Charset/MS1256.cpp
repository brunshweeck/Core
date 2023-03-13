//
// Created by brunshweeck on 28/02/2023.
//

#include "MS1256.h"
#include "../String.h"
#include "../Character.h"
static gchar bytesToChar[] =
        u"\u20AC\u067E\u201A\u0192\u201E\u2026\u2020\u2021"       // 0x80 - 0x87
        "\u02C6\u2030\u0679\u2039\u0152\u0686\u0698\u0688"       // 0x88 - 0x8f
        "\u06AF\u2018\u2019\u201C\u201D\u2022\u2013\u2014"       // 0x90 - 0x97
        "\u06A9\u2122\u0691\u203A\u0153\u200C\u200D\u06BA"       // 0x98 - 0x9f
        "\u00A0\u060C\u00A2\u00A3\u00A4\u00A5\u00A6\u00A7"       // 0xa0 - 0xa7
        "\u00A8\u00A9\u06BE\u00AB\u00AC\u00AD\u00AE\u00AF"       // 0xa8 - 0xaf
        "\u00B0\u00B1\u00B2\u00B3\u00B4\u00B5\u00B6\u00B7"       // 0xb0 - 0xb7
        "\u00B8\u00B9\u061B\u00BB\u00BC\u00BD\u00BE\u061F"       // 0xb8 - 0xbf
        "\u06C1\u0621\u0622\u0623\u0624\u0625\u0626\u0627"       // 0xc0 - 0xc7
        "\u0628\u0629\u062A\u062B\u062C\u062D\u062E\u062F"       // 0xc8 - 0xcf
        "\u0630\u0631\u0632\u0633\u0634\u0635\u0636\u00D7"       // 0xd0 - 0xd7
        "\u0637\u0638\u0639\u063A\u0640\u0641\u0642\u0643"       // 0xd8 - 0xdf
        "\u00E0\u0644\u00E2\u0645\u0646\u0647\u0648\u00E7"       // 0xe0 - 0xe7
        "\u00E8\u00E9\u00EA\u00EB\u0649\u064A\u00EE\u00EF"       // 0xe8 - 0xef
        "\u064B\u064C\u064D\u064E\u00F4\u064F\u0650\u00F7"       // 0xf0 - 0xf7
        "\u0651\u00F9\u0652\u00FB\u00FC\u200E\u200F\u06D2"       // 0xf8 - 0xff
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

MS1256::MS1256() : Charset("Windows-1256") {}

MS1256 MS1256::INSTANCE{};

String MS1256::name() const {
    return "Windows-1256";
}

gchar MS1256::decode(gint b) {
    return bytesToChar[b + 128];
}

Charset::CoderResult MS1256::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
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

Charset::CoderResult MS1256::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
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
                                cr = Charset::CoderResult::UNDERFLOW;
                            } else {
                                uc = -1;
                                errorLength = 1;
                                cr = Charset::CoderResult::MALFORMED;
                            }
                        }
                    } else if (Character::isLowSurrogate(c)) {
                        uc = -1;
                        errorLength = 1;
                        cr = Charset::CoderResult::MALFORMED;
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

gfloat MS1256::averageCharsPerByte() const {
    return 1;
}

gfloat MS1256::averageBytesPerChar() const {
    return 1;
}

gbool MS1256::contains(const Charset &cs) const {
    return dynamic_cast<MS1256 const *>(&cs) || name().equals("US-ASCII");
}

Object &MS1256::clone() const {
    static MS1256 ms1256 = MS1256();
    return ms1256;
}

gint MS1256::encode(gchar ch) {
    gchar index = charToBytes_indexes[ch >> 8];
    if (index == UNMAPPABLE_ENCODING)
        return UNMAPPABLE_ENCODING;
    return charToBytes[index + (ch & 0xff)];
}

Charset::ErrorAction MS1256::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction MS1256::unmappableAction() const {
    return Charset::unmappableAction();
}

CharBuffer MS1256::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer MS1256::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String MS1256::toString() const {
    return Charset::toString();
}

