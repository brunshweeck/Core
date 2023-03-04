//
// Created by brunshweeck on 28/02/2023.
//

#include "MS1251.h"
#include "../String.h"

static gchar bytesToChar[] =
        u"\u0402\u0403\u201A\u0453\u201E\u2026\u2020\u2021"       // 0x80 - 0x87
        "\u20AC\u2030\u0409\u2039\u040A\u040C\u040B\u040F"       // 0x88 - 0x8f
        "\u0452\u2018\u2019\u201C\u201D\u2022\u2013\u2014"       // 0x90 - 0x97
        "\uFFFD\u2122\u0459\u203A\u045A\u045C\u045B\u045F"       // 0x98 - 0x9f
        "\u00A0\u040E\u045E\u0408\u00A4\u0490\u00A6\u00A7"       // 0xa0 - 0xa7
        "\u0401\u00A9\u0404\u00AB\u00AC\u00AD\u00AE\u0407"       // 0xa8 - 0xaf
        "\u00B0\u00B1\u0406\u0456\u0491\u00B5\u00B6\u00B7"       // 0xb0 - 0xb7
        "\u0451\u2116\u0454\u00BB\u0458\u0405\u0455\u0457"       // 0xb8 - 0xbf
        "\u0410\u0411\u0412\u0413\u0414\u0415\u0416\u0417"       // 0xc0 - 0xc7
        "\u0418\u0419\u041A\u041B\u041C\u041D\u041E\u041F"       // 0xc8 - 0xcf
        "\u0420\u0421\u0422\u0423\u0424\u0425\u0426\u0427"       // 0xd0 - 0xd7
        "\u0428\u0429\u042A\u042B\u042C\u042D\u042E\u042F"       // 0xd8 - 0xdf
        "\u0430\u0431\u0432\u0433\u0434\u0435\u0436\u0437"       // 0xe0 - 0xe7
        "\u0438\u0439\u043A\u043B\u043C\u043D\u043E\u043F"       // 0xe8 - 0xef
        "\u0440\u0441\u0442\u0443\u0444\u0445\u0446\u0447"       // 0xf0 - 0xf7
        "\u0448\u0449\u044A\u044B\u044C\u044D\u044E\u044F"       // 0xf8 - 0xff
        "\u0000\u0001\u0002\u0003\u0004\u0005\u0006\u0007"       // 0x00 - 0x07
        "\b\t\n\u000B\f\r\u000E\u000F"                          // 0x08 - 0x0f
        "\u0010\u0011\u0012\u0013\u0014\u0015\u0016\u0017"       // 0x10 - 0x17
        "\u0018\u0019\u001A\u001B\u001C\u001D\u001E\u001F"       // 0x18 - 0x1f
        "\u0020\u0021\"\u0023\u0024\u0025\u0026\'"              // 0x20 - 0x27
        "\u0028\u0029\u002A\u002B\u002C\u002D\u002E\u002F"       // 0x28 - 0x2f
        "\u0030\u0031\u0032\u0033\u0034\u0035\u0036\u0037"       // 0x30 - 0x37
        "\u0038\u0039\u003A\u003B\u003C\u003D\u003E\u003F"       // 0x38 - 0x3f
        "\u0040\u0041\u0042\u0043\u0044\u0045\u0046\u0047"       // 0x40 - 0x47
        "\u0048\u0049\u004A\u004B\u004C\u004D\u004E\u004F"       // 0x48 - 0x4f
        "\u0050\u0051\u0052\u0053\u0054\u0055\u0056\u0057"       // 0x50 - 0x57
        "\u0058\u0059\u005A\u005B\\\u005D\u005E\u005F"             // 0x58 - 0x5f
        "\u0060\u0061\u0062\u0063\u0064\u0065\u0066\u0067"       // 0x60 - 0x67
        "\u0068\u0069\u006A\u006B\u006C\u006D\u006E\u006F"       // 0x68 - 0x6f
        "\u0070\u0071\u0072\u0073\u0074\u0075\u0076\u0077"       // 0x70 - 0x77
        "\u0078\u0079\u007A\u007B\u007C\u007D\u007E\u007F";      // 0x78 - 0x7f
static gchar charToBytes[0x500] = u"";
static gchar charToBytes_indexes[0x100] = u"";
static gchar charToBytes_NR[0] = {};
static CORE_FAST gchar UNMAPPABLE_DECODING = 0xFFFD;
static CORE_FAST gint UNMAPPABLE_ENCODING = 0xFFFD;

static gint initC2B() {
    for (char16_t &charToBytes_index: charToBytes_indexes)
        charToBytes_index = 0xFFFD;
    for (char16_t &charToByte: charToBytes)
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

MS1251::MS1251() : Charset("Windows-1251") {}

String MS1251::name() const {
    return "Windows-1251";
}

gchar MS1251::decode(gint b) {
    return bytesToChar[b + 128];
}

Charset::CoderResult MS1251::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
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

Charset::CoderResult MS1251::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
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

gfloat MS1251::averageCharsPerByte() const {
    return 1;
}

gfloat MS1251::averageBytesPerChar() const {
    return 1;
}

gbool MS1251::contains(const Charset &cs) const {
    return dynamic_cast<MS1251 const *>(&cs) || name().equals("US-ASCII");
}

Object &MS1251::clone() const {
    static MS1251 ms1251 = MS1251();
    return ms1251;
}

gint MS1251::encode(gchar ch) {
    gchar index = charToBytes_indexes[ch >> 8];
    if (index == UNMAPPABLE_ENCODING)
        return UNMAPPABLE_ENCODING;
    return charToBytes[index + (ch & 0xff)];
}

