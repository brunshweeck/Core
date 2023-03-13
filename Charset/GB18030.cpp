//
// Created by brunshweeck on 05/03/2023.
//

#include "GB18030.h"
#include "../String.h"
#include "../Character.h"

static CORE_FAST gint GB18030_SINGLE_BYTE = 1;
static CORE_FAST gint GB18030_DOUBLE_BYTE = 2;
static CORE_FAST gint GB18030_FOUR_BYTE = 3;
static gint currentState = GB18030_DOUBLE_BYTE;

static gint getGB18030(gshort const outerIndex[], String const innerEncoderIndex[], gchar ch) {
    gint offset = outerIndex[((ch & 0xff00) >> 8)] << 8;
    return innerEncoderIndex[offset >> 12].charAt((offset & 0xfff) + (ch & 0xff));
}

GB18030::GB18030() : Charset("GB18030") {}

GB18030 GB18030::INSTANCE{};

String GB18030::name() const {
    return "GB18030";
}

Charset::ErrorAction GB18030::malformedAction() const {
    return Charset::malformedAction();
}

Charset::ErrorAction GB18030::unmappableAction() const {
    return Charset::unmappableAction();
}

Charset::CoderResult GB18030::decodeLoop(ByteBuffer &src, CharBuffer &dst) {
    gint mark = src.position();

    try {
        while (src.hasRemaining()) {
            gint byte1 = 0, byte2 = 0, byte3 = 0, byte4 = 0;
            byte1 = src.get() & 0xFF;
            gint inputSize = 1;

            if ((byte1 & (gbyte) 0x80) == 0) { // US-ASCII range
                currentState = GB18030_SINGLE_BYTE;
            } else if (byte1 < 0x81 || byte1 > 0xfe) {
                errorLength = 1;
                return CoderResult::MALFORMED;
            } else { // Either 2 or 4 gbyte sequence follows
                if (src.remaining() < 1)
                    return CoderResult::UNDERFLOW;
                byte2 = src.get() & 0xFF;
                inputSize = 2;

                if (byte2 < 0x30) {
                    errorLength = 1;
                    return CoderResult::MALFORMED;
                } else if (byte2 >= 0x30 && byte2 <= 0x39) {
                    currentState = GB18030_FOUR_BYTE;

                    if (src.remaining() < 2)
                        return CoderResult::UNDERFLOW;

                    byte3 = src.get() & 0xFF;
                    if (byte3 < 0x81 || byte3 > 0xfe) {
                        errorLength = 3;
                        return CoderResult::MALFORMED;
                    }

                    byte4 = src.get() & 0xFF;
                    inputSize = 4;

                    if (byte4 < 0x30 || byte4 > 0x39) {
                        errorLength = 4;
                        return CoderResult::MALFORMED;
                    }
                } else if (byte2 == 0x7f || byte2 == 0xff || (byte2 < 0x40)) {
                    errorLength = 2;
                    return CoderResult::MALFORMED;
                } else
                    currentState = GB18030_DOUBLE_BYTE;
            }

            if (dst.remaining() < 1)
                return CoderResult::OVERFLOW;
            switch (currentState) {
                case GB18030_SINGLE_BYTE:
                    dst.put((gchar) byte1);
                    break;
                case GB18030_DOUBLE_BYTE:
                    dst.put(decodeDouble(byte1, byte2));
                    break;
                case GB18030_FOUR_BYTE:
                    gint offset = (((byte1 - 0x81) * 10 + (byte2 - 0x30)) * 126 + byte3 - 0x81) * 10 + byte4 - 0x30;
                    gint hiByte = (offset >> 8) & 0xFF;
                    gint lowByte = (offset & 0xFF);

                    // Mixture of table lookups and algorithmic calculation
                    // of character values.

                    // BMP Ranges
                    if (offset <= 0x4A62)
                        dst.put(getChar(offset));
                    else if (offset > 0x4A62 && offset <= 0x82BC)
                        dst.put((gchar) (offset + 0x5543));
                    else if (offset >= 0x82BD && offset <= 0x830D)
                        dst.put(getChar(offset));
                    else if (offset >= 0x830D && offset <= 0x93A8)
                        dst.put((gchar) (offset + 0x6557));
                    else if (offset >= 0x93A9 && offset <= 0x99FB)
                        dst.put(getChar(offset));
                        // Supplemental UCS planes handled via surrogates
                    else if (offset >= 0x2E248 && offset < 0x12E248) {
                        if (offset >= 0x12E248) {
                            errorLength = 4;
                            return CoderResult::MALFORMED;
                        }
                        offset -= 0x1e248;
                        if (dst.remaining() < 2)
                            return CoderResult::OVERFLOW;
                        // emit high + low surrogate
                        dst.put((gchar) ((offset - 0x10000) / 0x400 + 0xD800));
                        dst.put((gchar) ((offset - 0x10000) % 0x400 + 0xDC00));
                    } else {
                        errorLength = inputSize;
                        return CoderResult::MALFORMED;
                    }
            }
            mark += inputSize;
        }
        return CoderResult::UNDERFLOW;
    } catch (...) {
        src.position(mark);
    }
    return CoderResult::UNDERFLOW;
}

Charset::CoderResult GB18030::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    struct Surrogate {
        gint &errorLength;
        gint isPair = false;
        Charset::CoderResult error = Charset::CoderResult::UNDERFLOW;
        gint character = 0;

        gint parse(gchar c, CharBuffer &in) {
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
    Surrogate sgp = {errorLength};
    gint condensedKey = 0;
    gint hiByte = 0, loByte = 0;
    currentState = GB18030_DOUBLE_BYTE;
    gint mark = src.position();
    try {
        while (src.hasRemaining()) {
            gchar c = src.get();
            gint inputSize = 1;
            if (Character::isSurrogate(c)) {
                if ((condensedKey = sgp.parse(c, src)) < 0)
                    return sgp.error;
                condensedKey += 0x1e248;
                currentState = GB18030_FOUR_BYTE;
                inputSize = 2;
            } else if (c >= 0x0000 && c <= 0x007F) {
                currentState = GB18030_SINGLE_BYTE;
            } else if (c <= 0xA4C6 || c >= 0xE000) {
                gint outByteVal = getGB18030(encoderIndex1, encoderIndex2, c);
                if (outByteVal == 0xFFFD) {
                    errorLength = 1;
                    return CoderResult::UNMAPPABLE;
                }

                hiByte = (outByteVal & 0xFF00) >> 8;
                loByte = (outByteVal & 0xFF);

                condensedKey = (hiByte - 0x20) * 256 + loByte;

                if (c >= 0xE000 && c < 0xF900)
                    condensedKey += 0x82BD;
                else if (c >= 0xF900)
                    condensedKey += 0x93A9;

                if (hiByte > 0x80)
                    currentState = GB18030_DOUBLE_BYTE;
                else
                    currentState = GB18030_FOUR_BYTE;
            } else if (c >= 0xA4C7 && c <= 0xD7FF) {
                condensedKey = c - 0x5543;
                currentState = GB18030_FOUR_BYTE;
            }

            if (currentState == GB18030_SINGLE_BYTE) {
                if (dst.remaining() < 1)
                    return CoderResult::OVERFLOW;
                dst.put((gbyte) c);
            } else if (currentState == GB18030_DOUBLE_BYTE) {
                if (dst.remaining() < 2)
                    return CoderResult::OVERFLOW;
                dst.put((gbyte) hiByte);
                dst.put((gbyte) loByte);
            } else { // Four gbyte encoding
                gbyte b1, b2, b3, b4;

                if (dst.remaining() < 4)
                    return CoderResult::OVERFLOW;
                // Decompose the condensed key into its 4 gbyte equivalent
                b4 = (gbyte) ((condensedKey % 10) + 0x30);
                condensedKey /= 10;
                b3 = (gbyte) ((condensedKey % 126) + 0x81);
                condensedKey /= 126;
                b2 = (gbyte) ((condensedKey % 10) + 0x30);
                b1 = (gbyte) ((condensedKey / 10) + 0x81);
                dst.put(b1);
                dst.put(b2);
                dst.put(b3);
                dst.put(b4);
            }
            mark += inputSize;
        }
        return CoderResult::UNDERFLOW;
    } catch (...) {
        src.position(mark);
    }
    return CoderResult::UNDERFLOW;
}

gfloat GB18030::averageCharsPerByte() const {
    return 1.0f;
}

gfloat GB18030::averageBytesPerChar() const {
    return 4.0f;
}

CharBuffer GB18030::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer GB18030::encode(CharBuffer &in) {
    return Charset::encode(in);
}

String GB18030::toString() const {
    return Charset::toString();
}

gbool GB18030::contains(const Charset &cs) const {
    return ((cs.name().equals("US-ASCII"))
            || (cs.name().equals("GBK"))
            || (cs.name().equals("ISO-8859-1"))
            || (cs.name().equals("ISO-8859-2"))
            || (cs.name().equals("ISO-8859-3"))
            || (cs.name().equals("ISO-8859-4"))
            || (cs.name().equals("ISO-8859-5"))
            || (cs.name().equals("ISO-8859-6"))
            || (cs.name().equals("ISO-8859-7"))
            || (cs.name().equals("ISO-8859-8"))
            || (cs.name().equals("ISO-8859-9"))
            || (cs.name().equals("ISO-8859-13"))
            || (cs.name().equals("ISO-8859-15"))
            || (cs.name().equals("ISO-8859-16"))
            || (cs.name().equals("UTF-8"))
            || (cs.name().equals("UTF-16"))
            || (cs.name().equals("UTF-16LE"))
            || (cs.name().equals("UTF-16BE"))
            || (cs.name().equals("windows-1251"))
            || (cs.name().equals("windows-1252"))
            || (cs.name().equals("windows-1253"))
            || (cs.name().equals("windows-1254"))
            || (cs.name().equals("windows-1255"))
            || (cs.name().equals("windows-1256"))
            || (cs.name().equals("windows-1257"))
            || (cs.name().equals("windows-1258"))
            || (cs.name().equals("windows-932"))
            || (cs.name().equals("x-mswin-936"))
            || (cs.name().equals("x-windows-949"))
            || (cs.name().equals("x-windows-950"))
            || (cs.name().equals("windows-31j"))
            || (cs.name().equals("JIS_X0201"))
            || (cs.name().equals("JIS_X0208-1990"))
            || (cs.name().equals("JIS_X0212"))
            || (cs.name().equals("Shift_JIS"))
            || (cs.name().equals("GB2312"))
            || (cs.name().equals("EUC-KR"))
            || (cs.name().equals("x-EUC-TW"))
            || (cs.name().equals("EUC-JP"))
            || (cs.name().equals("euc-jp-linux"))
            || (cs.name().equals("KOI8-R"))
            || (cs.name().equals("TIS-620"))
            || (cs.name().equals("x-ISCII91"))
            || (cs.name().equals("Big5"))
            || (cs.name().equals("Big5-HKSCS"))
            || (cs.name().equals("x-MS950-HKSCS"))
            || (cs.name().equals("ISO-2022-JP"))
            || (cs.name().equals("ISO-2022-KR"))
            || (cs.name().equals("x-ISO-2022-CN-CNS"))
            || (cs.name().equals("x-ISO-2022-CN-GB"))
            || (cs.name().equals("x-Johab"))
            || (dynamic_cast<GB18030 const *>(&cs)));
}

gbool GB18030::canEncode(gchar c) const {
    return Charset::canEncode(c);
}

Object &GB18030::clone() const {
    return INSTANCE;
}

gchar GB18030::getChar(gint offset) {
    gint byte1 = (offset >> 8) & 0xFF;
    gint byte2 = (offset & 0xFF);
    gint start = 0, end = 0xFF;

    if (((byte1 < 0) || (byte1 > sizeof(decoderIndex1) / sizeof(gshort))) || ((byte2 < start) || (byte2 > end))) {
        return REPLACE_CHAR;
    }

    gint n = (decoderIndex1[byte1] & 0xf) * (end - start + 1) + (byte2 - start);
    return decoderIndex2[decoderIndex1[byte1] >> 4].charAt(n);
}

gchar GB18030::decodeDouble(gint byte1, gint byte2) {
    gint start = 0x40, end = 0xFE;
    if (((byte1 < 0) || (byte1 > sizeof(index1) / sizeof(gshort)))
        || ((byte2 < start) || (byte2 > end)))
        return u'\uFFFD';

    gint n = (index1[byte1] & 0xf) * (end - start + 1) + (byte2 - start);
    return index2[index1[byte1] >> 4].charAt(n);
}


