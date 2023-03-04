//
// Created by brunshweeck on 26/02/2023.
//
#include "UTF8.h"
#include "../String.h"

gbool UTF8::isNotContinuation(gint b) {
    return (b & 0xc0) != 0x80;
}

gbool UTF8::isMalformed3(gint b1, gint b2, gint b3) {
    return (b1 == (gbyte) 0xe0 && (b2 & 0xe0) == 0x80) ||
           (b2 & 0xc0) != 0x80 || (b3 & 0xc0) != 0x80;
}

gbool UTF8::isMalformed3(gint b1, gint b2) {
    return (b1 == (gbyte) 0xe0 && (b2 & 0xe0) == 0x80) ||
           (b2 & 0xc0) != 0x80;
}

gbool UTF8::isMalformed4(gint b2, gint b3, gint b4) {
    return (b2 & 0xc0) != 0x80 || (b3 & 0xc0) != 0x80 ||
           (b4 & 0xc0) != 0x80;
}

gbool UTF8::isMalformed4(gint b1, gint b2) {
    return (b1 == 0xf0 && (b2 < 0x90 || b2 > 0xbf)) ||
           (b1 == 0xf4 && (b2 & 0xf0) != 0x80) ||
           (b2 & 0xc0) != 0x80;
}

gbool UTF8::isMalformed4(gint b3) {
    return (b3 & 0xc0) != 0x80;
}

String UTF8::name() const {
    return "UTF8";
}

UTF8::UTF8() : Unicode(u"UTF-8") {}

UTF8 UTF8::INSTANCE{};

Charset::ErrorAction UTF8::malformedAction() const {
    return Charset::ErrorAction::REPORT;
}

Charset::ErrorAction UTF8::unmappableAction() const {
    return ErrorAction::REPORT;
}

static Charset::CoderResult xflow(Buffer &src, gint srcPos, gint srcLim, Buffer &dst, gint dstPos, gint length) {
    src.position(srcPos - src.offset());
    dst.position(dstPos - dst.offset());
    return length == 0 || srcLim - srcPos < length ? Charset::CoderResult::UNDERFLOW :
           Charset::CoderResult::OVERFLOW;
}

static Charset::CoderResult xflow(Buffer &src, gint mark, gint length) {
    src.position(mark);
    return length == 0 || src.remaining() < length ? Charset::CoderResult::UNDERFLOW :
           Charset::CoderResult::OVERFLOW;
}

static gint len = 0;
gint &Charset::errorLength = len;

static Charset::CoderResult malformedN(ByteBuffer &src, gint nb) {
    len = 0;
    switch (nb) {
        case 1:
        case 2:                    // always 1
            len = 1;
            return Charset::CoderResult::MALFORMED;
        case 3: {
            gint b1 = src.get();
            gint b2 = src.get();    // no need to lookup b3
            len = ((b1 == (gbyte) 0xe0 && (b2 & 0xe0) == 0x80 || (b2 & 0xc0) != 0x80) ? 1 : 2);
            return Charset::CoderResult::MALFORMED;
        }
        case 4:  // we don't care the speed here
        {
            gint b1 = src.get() & 0xff;
            gint b2 = src.get() & 0xff;
            if (b1 > 0xf4 || (b1 == 0xf0 && (b2 < 0x90 || b2 > 0xbf)) || (b1 == 0xf4 && (b2 & 0xf0) != 0x80) ||
                (b2 & 0xc0) != 0x80) {
                len = 1;
                return Charset::CoderResult::MALFORMED;
            }
            if ((src.get() & 0xc0) != 0x80) {
                len = 2;
            } else
                len = 3;
            return Charset::CoderResult::MALFORMED;
        }
        default:
            len = 0;
            return Charset::CoderResult::MALFORMED;
    }
}

static void updatePositions(Buffer &src, gint sp, Buffer &dst, gint dp) {
    src.position(sp - src.offset());
    dst.position(dp - dst.offset());
}

static Charset::CoderResult malformed(ByteBuffer &src, gint sp, CharBuffer &dst, gint dp, gint nb) {
    src.position(sp - src.offset());
    Charset::CoderResult cr = malformedN(src, nb);
    updatePositions(src, sp, dst, dp);
    return cr;
}


static Charset::CoderResult malformed(ByteBuffer &src, gint mark, gint nb) {
    src.position(mark);
    Charset::CoderResult cr = malformedN(src, nb);
    src.position(mark);
    return cr;
}

static Charset::CoderResult malformedForLength(ByteBuffer &src, gint sp, CharBuffer &dst, gint dp, gint malformedNB) {
    updatePositions(src, sp, dst, dp);
    len = malformedNB;
    return Charset::CoderResult::MALFORMED;
}

static Charset::CoderResult malformedForLength(ByteBuffer &src, gint mark, gint malformedNB) {
    src.position(mark);
    len = malformedNB;
    return Charset::CoderResult::MALFORMED;
}

Charset::CoderResult UTF8::decodeLoop(ByteBuffer &in, CharBuffer &out) {
    gint mark = in.position();
    gint limit = in.limit();
    while (mark < limit) {
        gint b1 = in.get();
        if (b1 >= 0) {
            // 1 byte, 7 bits 0xxxxxxx
            if (out.remaining() < 1)
                return xflow(in, mark, 1);
            out.put((gchar) b1);
            mark = mark + 1;
        } else if ((b1 >> 5) == -2 && (b1 & 0x1e) != 0) {
            // 2 bytes, 11 bits: 110xxxxx 10xxxxxx
            if (limit - mark < 2 || out.remaining() < 1)
                return xflow(in, mark, 2);
            gint b2 = in.get();
            if (isNotContinuation(b2)) {
                return malformedForLength(in, mark, 2);
            }
            out.put((gchar) (((b1 << 6) ^ b2) ^ (((gbyte) 0xC0 << 6) ^ ((gbyte) 0x80 << 0))));
            mark = mark + 2;
        } else if ((b1 >> 4) == -2) {
            // 3 bytes, 16 bits: 1110xxxx 10xxxxxx 10xxxxxx
            gint inRemaining = limit - mark;
            if (inRemaining < 3 || out.remaining() < 1) {
                if (inRemaining > 1 && isMalformed3(b1, in.get()))
                    return malformedForLength(in, mark, 1);
                return xflow(in, mark, 3);
            }
            gint b2 = in.get();
            gint b3 = in.get();
            if (isMalformed3(b1, b2, b3))
                return malformed(in, mark, 3);
            gchar c = (gchar) ((b1 << 12) ^ (b2 << 6) ^
                               (b3 ^ (((gbyte) 0xE0 << 12) ^ ((gbyte) 0x80 << 6) ^ ((gbyte) 0x80 << 0))));
            if (Character::isSurrogate(c))
                return malformedForLength(in, mark, 3);
            out.put(c);
            mark += 3;
        } else if ((b1 >> 3) == -2) {
            // 4 bytes, 21 bits: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            gint inRemaining = limit - mark;
            if (inRemaining < 4 || out.remaining() < 2) {
                b1 &= 0xff;
                if (b1 > 0xf4 ||
                    inRemaining > 1 && isMalformed4(b1, in.get() & 0xff))
                    return malformedForLength(in, mark, 1);
                if (inRemaining > 2 && isMalformed4(in.get()))
                    return malformedForLength(in, mark, 2);
                return xflow(in, mark, 4);
            }
            gint b2 = in.get();
            gint b3 = in.get();
            gint b4 = in.get();
            gint uc = ((b1 << 18) ^ (b2 << 12) ^ (b3 << 6) ^
                      (b4 ^ (((gbyte) 0xF0 << 18) ^ ((gbyte) 0x80 << 12) ^
                             ((gbyte) 0x80 << 6) ^ ((gbyte) 0x80 << 0))));
            if (isMalformed4(b2, b3, b4) ||
                // shortest form check
                !Character::isSupplementary(uc)) {
                return malformed(in, mark, 4);
            }
            out.put(Character::highSurrogate(uc));
            out.put(Character::lowSurrogate(uc));
            mark += 4;
        } else {
            return malformed(in, mark, 1);
        }
    }
    return xflow(in, mark, 0);
}

static Charset::CoderResult overflow(CharBuffer &src, gint sp, ByteBuffer &dst, gint dp) {
    updatePositions(src, sp, dst, dp);
    return Charset::CoderResult::OVERFLOW;
}

static Charset::CoderResult overflow(CharBuffer& src, gint mark) {
    src.position(mark);
    return Charset::CoderResult::OVERFLOW;
}

Charset::CoderResult UTF8::encodeLoop(CharBuffer &src, ByteBuffer &dst) {
    gint mark = src.position();
    while (src.hasRemaining()) {
        gchar c = src.get();
        if (c < 0x80) {
            // Have at most seven bits
            if (!dst.hasRemaining())
                return overflow(src, mark);
            dst.put((gbyte) c);
        } else if (c < 0x800) {
            // 2 bytes, 11 bits
            if (dst.remaining() < 2)
                return overflow(src, mark);
            dst.put((gbyte) (0xc0 | (c >> 6)));
            dst.put((gbyte) (0x80 | (c & 0x3f)));
        } else if (Character::isSurrogate(c)) {
            // Have a surrogate pair
            CoderResult cr = Charset::CoderResult::UNDERFLOW;
            gint uc = 0;
            if(Character::isHighSurrogate(c)) {
                if(!src.hasRemaining()){
                    cr = Charset::CoderResult::UNDERFLOW;
                    uc = -1;
                }
                else {
                    gchar d = src.get();
                    if(Character::isLowSurrogate(c)){
                        uc = Character::joinSurrogates(c, d);
                        cr = Charset::CoderResult::NONE;
                    }else
                        uc = -1;
                }
            }
            else if(Character::isLowSurrogate(c)){
                uc = -1;
                errorLength = 1;
                cr = Charset::CoderResult::MALFORMED;
            }
            else {
                uc = c;
                cr = Charset::CoderResult::NONE;
            }
            if (uc < 0) {
                src.position(mark);
                return cr;
            }
            if (dst.remaining() < 4)
                return overflow(src, mark);
            dst.put((gbyte) (0xf0 | ((uc >> 18))));
            dst.put((gbyte) (0x80 | ((uc >> 12) & 0x3f)));
            dst.put((gbyte) (0x80 | ((uc >> 6) & 0x3f)));
            dst.put((gbyte) (0x80 | (uc & 0x3f)));
            mark++;  // 2 chars
        } else {
            // 3 bytes, 16 bits
            if (dst.remaining() < 3)
                return overflow(src, mark);
            dst.put((gbyte) (0xe0 | ((c >> 12))));
            dst.put((gbyte) (0x80 | ((c >> 6) & 0x3f)));
            dst.put((gbyte) (0x80 | (c & 0x3f)));
        }
        mark++;
    }
    src.position(mark);
    return CoderResult::UNDERFLOW;
}

gfloat UTF8::averageCharsPerByte() const {
    return 1.0f;
}

gfloat UTF8::averageBytesPerChar() const {
    return 1.1f;
}

Object &UTF8::clone() const {
    return INSTANCE;
}

CharBuffer UTF8::decode(ByteBuffer &in) {
    return Charset::decode(in);
}

ByteBuffer UTF8::encode(CharBuffer &in) {
    return Charset::encode(in);
}

