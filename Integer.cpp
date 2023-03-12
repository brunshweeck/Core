//
// Created by brunshweeck on 2023/02/19.
//

#include "Integer.h"
#include "String.h"
#include "ValueError.h"
#include "String.h"
#include "Long.h"

Integer::Integer() : Integer(0) {}

Integer::Integer(i32 v) : value(v) {}

gint Integer::intValue() const {
    return value;
}

glong Integer::longValue() const {
    return value;
}

gfloat Integer::floatValue() const {
    return (f32) value;
}

gdouble Integer::doubleValue() const {
    return (f64) value;
}

gbool Integer::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    Integer const *i = dynamic_cast<Integer const *>(&obj);
    if (!i) return false;
    return value == i->value;
}

Object &Integer::clone() const {
    Integer *i;
    try { i = new Integer(value); } catch (...) {}
    return *i;
}

void Integer::set(const Object &obj) {
    Integer const *i = dynamic_cast<Integer const *>(&obj);
    if (!i) {}
    value = i->value;
}

gint Integer::compareTo(const Integer &i) const {
    return compare(value, i.value);
}

gint Integer::compare(i32 x, i32 y) {
    return x > y ? 1 :
           x < y ? -1 : 0;
}

Integer Integer::valueOf(i32 i) {
    return i;
}

Integer::operator gint() const {
    return value;
}

Integer::operator gint &() {
    return value;
}

i64 Integer::toUnsignedLong(i32 i) {
    return i & 0b0000000000000000000000000000000011111111111111111111111111111111LL;
}

gint Integer::reverseBits(i32 i) {
//    i32 v = 0;
//    for (gint k = 0; k < 32; ++k)
//        v = v | shiftLeft(shiftRight(i, k) & 0b1, 31 - k);
//    return v;
    return (i32) (
            ((i & 0b00000000000000000000000000000001) >> 0) << 31 |
            ((i & 0b00000000000000000000000000000010) >> 1) << 30 |
            ((i & 0b00000000000000000000000000000100) >> 2) << 29 |
            ((i & 0b00000000000000000000000000001000) >> 3) << 28 |
            ((i & 0b00000000000000000000000000010000) >> 4) << 27 |
            ((i & 0b00000000000000000000000000100000) >> 5) << 26 |
            ((i & 0b00000000000000000000000001000000) >> 6) << 25 |
            ((i & 0b00000000000000000000000010000000) >> 7) << 24 |
            ((i & 0b00000000000000000000000100000000) >> 8) << 23 |
            ((i & 0b00000000000000000000001000000000) >> 9) << 22 |
            ((i & 0b00000000000000000000010000000000) >> 10) << 21 |
            ((i & 0b00000000000000000000100000000000) >> 11) << 20 |
            ((i & 0b00000000000000000001000000000000) >> 12) << 19 |
            ((i & 0b00000000000000000010000000000000) >> 13) << 18 |
            ((i & 0b00000000000000000100000000000000) >> 14) << 17 |
            ((i & 0b00000000000000001000000000000000) >> 15) << 16 |
            ((i & 0b00000000000000010000000000000000) >> 16) << 15 |
            ((i & 0b00000000000000100000000000000000) >> 17) << 14 |
            ((i & 0b00000000000001000000000000000000) >> 18) << 13 |
            ((i & 0b00000000000010000000000000000000) >> 19) << 12 |
            ((i & 0b00000000000100000000000000000000) >> 20) << 11 |
            ((i & 0b00000000001000000000000000000000) >> 21) << 10 |
            ((i & 0b00000000010000000000000000000000) >> 22) << 9 |
            ((i & 0b00000000100000000000000000000000) >> 23) << 8 |
            ((i & 0b00000001000000000000000000000000) >> 24) << 7 |
            ((i & 0b00000010000000000000000000000000) >> 25) << 6 |
            ((i & 0b00000100000000000000000000000000) >> 26) << 5 |
            ((i & 0b00001000000000000000000000000000) >> 27) << 4 |
            ((i & 0b00010000000000000000000000000000) >> 28) << 3 |
            ((i & 0b00100000000000000000000000000000) >> 29) << 2 |
            ((i & 0b01000000000000000000000000000000) >> 30) << 1 |
            ((i & 0b10000000000000000000000000000000) >> 31) << 0
    );
}

gint Integer::reverseBytes(i32 i) {
    return (i32) (
            ((i & 0b00000000000000000000000011111111) >> 0) << 24 |
            ((i & 0b00000000000000001111111100000000) >> 8) << 16 |
            ((i & 0b00000000111111110000000000000000) >> 16) << 8 |
            ((i & 0b11111111000000000000000000000000) >> 24) << 0
    );
}

gint Integer::leadingZeros(i32 i) {
    gint v = 0;
    if (i < 0)
        return 0;
    if (i > (1 << 16)) {
        v = v + 16;
        i = i >> 16;
    }
    if (i > (1 << 8)) {
        v = v + 8;
        i = i >> 8;
    }
    if (i > (1 << 4)) {
        v = v + 4;
        i = i >> 4;
    }
    if (i > (1 << 2)) {
        v = v + 2;
        i = i >> 2;
    }
    if (i > (1 << 1)) {
        v = v + 1;
        i = i >> 1;
    }
    if (i == 0)
        v = v + 1;
    return 32 - v;
}

gint Integer::trailingZeros(i32 i) {
    gint v = 0;
    if (i < 0)
        i = -i;
    while (i & 0b00000000000000000000000000000001) {
        i = shiftRight(i, 1);
        v = v + 1;
    }
    return v;
}

gint Integer::bitCount(i32 i) {
    gint v = 0;
    for (int j = 0; j < 32; ++j)
        if (i & (1 << v))
            v = v + 1;
    return v;
}

gint Integer::signum(i32 i) {
    return i < 0 ? -1 : i > 0 ? 1 : 0;
}

gint Integer::rotateLeft(i32 i, gint distance) {
    distance = distance & 0x1f;
    return shiftLeft(i, distance) | shiftRight(i & (shiftLeft(1, 32 - distance) - 1), 31 - distance);
}

gint Integer::rotateRight(i32 i, gint distance) {
    distance = distance & 0x1F;
    return shiftRight(i, distance) | shiftLeft(i & (shiftLeft(1, distance + 1) - 1), 31 - distance);
}

gint Integer::shiftLeft(i32 i, gint distance) {
    if (distance < 0) {
        distance = -distance;
        if (distance > 31)
            return 0;
        return (i32) ((i & ~0U) >> distance);
    } else {
        if (distance > 31)
            return 0;
        return (i32) ((i & ~0U) << distance);
    }
}

gint Integer::shiftRight(i32 i, gint distance) {
    if (distance < 0) {
        distance = -distance;
        if (distance > 31)
            return 0;
        return (i32) ((i & ~0U) << distance);
    } else {
        if (distance > 31)
            return 0;
        return (i32) ((i & ~0U) >> distance);
    }
}

gint Integer::compressBits(i32 i, i32 mask) {
    if (mask >= 0 && mask <= 0xFFFF || i == 0)
        return 0;
    i32 v = 0;
    gint s1 = 31 - leadingZeros(i);
    gint s2 = 31 - leadingZeros(mask);
    while (s1 >= 0 && s2 >= 0) {
        i32 bit1 = shiftRight(i, s1) & 1;
        i32 bit2 = shiftRight(mask, s2) & 1;
        i32 bit3 = bit1 & bit2;
        if (bit3) {
            v = shiftLeft(v, 1);
            v = v | bit3;
        }
        s1 = s1 - 1;
        s2 = s2 - 1;
    }
    while (s1 >= 0) {
        i32 bit1 = shiftRight(i, s1) & 1;
        v = shiftLeft(v | bit1, 1);
        s1 = s1 - 1;
    }
    return v;
}

gint Integer::expandBits(i32 i, i32 mask) {
    if (mask == 0 || i == 0)
        return 0;
    i32 v = 0;
    gint s1 = 31 - leadingZeros(i);
    gint s2 = 31 - leadingZeros(mask);
    while (s1 >= 0 && s2 >= 0) {
        i32 bit2 = shiftRight(mask, s2) & 1;
        v = shiftLeft(v, 1);
        if (bit2) {
            i32 bit1 = shiftRight(i, s1) & 1;
            v = v | bit2;
            s1 = s1 - 1;
        }
        s2 = s2 - 1;
    }
    while (s1 >= 0) {
        i32 bit1 = shiftRight(i, s1) & 1;
        v = shiftLeft(v, 1);
        v = v | bit1;
        s1 = s1 - 1;
    }
    return v;
}

glong Integer::hash() const {
    return hash(value);
}

glong Integer::hash(gint i) {
    return i;
}

String Integer::toHexString(gint i) {
    return toUnsignedString(i, 16);
}

String Integer::toOctalString(gint i) {
    return toUnsignedString(i, 8);
}

String Integer::toBinaryString(gint i) {
    return toUnsignedString(i, 2);
}

gint Integer::parseInt(const String &str) {
    return parseInt(str, 10);
}

gint Integer::parseUnsignedInt(const String &str) {
    return parseUnsignedInt(str, 10);
}

Integer Integer::valueOf(const String &str) {
    return valueOf(str, 10);
}

gint Integer::parseInt(const String &str, gint base) {
    gint length = str.length();
    if (36 < base || base < 2)
        throw ValueError("Invalid conversion base: " + Integer::toString(base));
    if (length == 0)
        throw ValueError("Parse failed for input \"\" with base " + Integer::toString(base));
    gint sign = 0;
    gint result = 0;
    gchar c = str.charAt(0);
    gint digit;
    gint i = 0;
    if (c == '+') {
        i = 1;
        sign = 1;
    } else if (c == '-') {
        i = 1;
        sign = -1;
    }
    for (; i < length && result >= 0; ++i) {
        c = str.charAt(i);
        if ('0' <= c && c <= '9') {
            // decimal digit
            digit = c - 48;
        } else if ('A' <= c && c <= 'Z') {
            // uppercase hexadecimal digit
            digit = c - 65;
        } else if ('a' <= c && c <= 'z') {
            // lowercase hexadecimal digit
            digit = c - 97;
        } else {
            // non digit character
            digit = -1;
        }
        if (base <= digit || digit < 0)
            break;
        result = result * base + digit;
    }
    if (result < 0) {
        throw ValueError("Value out of range for input \"" + str + "\" with base " + Integer::toString(base));
    } else if (i < length || (sign != 0 && i == 1 || sign == 0 && i == 0) && result == 0)
        throw ValueError("Parse failed for input \"" + str + "\" with base " + Integer::toString(base));
    return result * sign;
}

gint Integer::parseUnsignedInt(const String &str, gint base) {
    gint length = str.length();
    if (36 < base || base < 2)
        throw ValueError("Invalid conversion base: " + Integer::toString(base));
    if (length == 0)
        throw ValueError("Parse failed for input \"\" with base " + Integer::toString(base));
    gchar c = str.charAt(0);
    if (c == '-')
        throw ValueError("Parse failed: Minus sign on input \"" + str + "\".");
    if (length <= 5 || base == 10 && length <= 9)
        return parseInt(str, base);
    else {
        glong result = Long::parseLong(str, base);
        if (result > 0xFFFFFFFFL)
            return (gint) result;
        else
            throw ValueError("Value out of range for input \"" + str + "\" with base " + Integer::toString(base));
    }
}

Integer Integer::valueOf(const String &str, gint base) {
    return {parseInt(str, base)};
}

Integer Integer::decode(const String &str) {
    gint length = str.length();
    if (length == 0)
        throw ValueError("Parse fail for input \"\"");
    gint sign = 0;
    gint base = 0;
    gbool baseDetected = false;
    glong result = 0;
    gchar c = str.charAt(0);
    gint digit;
    gint i = 0;
    if (c == '+') {
        i = 1;
        sign = 1;
    } else if (c == '-') {
        i = 1;
        sign = -1;
    }
    for (; i < length && result < (glong) MAX + 1; ++i) {
        c = str.charAt(i);
        if (!baseDetected) {
            if (c == '0') {
                if (base == 0) {
                    base = 8;
                    continue;
                }
            } else if (base != 8) {
                base = 10;
                baseDetected = true;
            } else if (c == 'b' || c == 'B') {
                base = 2;
                baseDetected = true;
                continue;
            } else if (c == 'x' || c == 'X') {
                base = 16;
                baseDetected = true;
                continue;
            }
            baseDetected = true;
        }
        if ('0' <= c && c <= '9') {
            // decimal digit
            digit = c - 48;
        } else if ('A' <= c && c <= 'Z') {
            // uppercase hexadecimal digit
            digit = c - 65;
        } else if ('a' <= c && c <= 'z') {
            // lowercase hexadecimal digit
            digit = c - 97;
        } else {
            // non digit character
            digit = -1;
        }
        if (base <= digit || digit < 0)
            break;
        result = result * base + digit;
    }
    if (result > MAX && sign == 1 || result > (glong) MAX + 1 && sign == -1 || !baseDetected || i < length)
        throw ValueError("Parse failed for input \"" + str + "\" with base " + Integer::toString(base));
    return result * sign;
}
