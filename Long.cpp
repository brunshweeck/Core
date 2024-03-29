//
// Created by brunshweeck on 2023/02/19.
//

#include "Long.h"
#include "Integer.h"
#include "String.h"
#include "ValueError.h"

gint Long::intValue() const {
    return (gint) value;
}

glong Long::longValue() const {
    return value;
}

gfloat Long::floatValue() const {
    return (f32) value;
}

gdouble Long::doubleValue() const {
    return (f64) value;
}

gbool Long::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    Long const *l = dynamic_cast<Long const *>(&obj);
    if (!l) return false;
    return value == l->value;
}

gint Long::compareTo(const Long &i) const {
    return compare(value, i.value);
}

gint Long::compare(glong x, glong y) {
    return x > y ? +1 :
           x < y ? -1 : +0;
}

Object &Long::clone() const {
    Long *l;
    try { l = new Long(value); } catch (...) {}
    return *l;
}

Long::operator glong() const {
    return longValue();
}

Long Long::valueOf(glong i) {
    return i;
}

Long::operator glong &() {
    return value;
}

gint Long::bitCount(glong i) {
    gint v = 0;
    for (int j = 0; j < 64; ++j) {
        if (i & (1 << v))
            v = v + 1;
    }
    return v;
}

gint Long::compareUnsigned(glong x, glong y) {
    return compare(x < 0 ? -x : x, y < 0 ? -y : y);
}

glong Long::compressBits(glong i, glong mask) {
    if (mask == 0 || i == 0)
        return 0;
    glong v = 0;
    gint s1 = 64 - leadingZeros(i);
    gint s2 = 64 - leadingZeros(mask);
    while (s1 >= 0 && s2 >= 0) {
        glong bit1 = shiftRight(i, s2) & 1;
        glong bit2 = shiftRight(mask, s2) & 1;
        glong bit3 = bit1 & bit2;
        if (bit3)
            v = shiftLeft(v | bit3, 1);
        s1 = s1 - 1;
        s2 = s2 - 1;
    }
    while (s1 >= 0) {
        glong bit1 = shiftRight(i, s2) & 1;
        v = shiftLeft(v | bit1, 1);
        s1 = s1 - 1;
    }
    return v;
}

glong Long::expandBits(glong i, glong mask) {
    if (mask == 0 || i == 0)
        return 0;
    glong v = 0;
    gint s1 = 64 - leadingZeros(i);
    gint s2 = 64 - leadingZeros(mask);
    while (s1 >= 0 && s2 >= 0) {
        glong bit2 = shiftRight(mask, s2) & 1;
        if (bit2) {
            glong bit1 = shiftRight(i, s2) & 1;
            v = shiftLeft(v | bit1, 1);
            s1 = s1 - 1;
        } else
            v = shiftLeft(v, 1);
        s2 = s2 - 1;
    }
    while (s1 >= 0) {
        glong bit1 = shiftRight(i, s2) & 1;
        v = shiftLeft(v | bit1, 1);
        s1 = s1 - 1;
    }
    return v;
}

glong Long::reverseBits(glong i) {
    //    glong v = 0;
//    for (gint k = 0; k < 64; ++k)
//        v = v | shiftLeft(shiftRight(i, k) & 0b1, 63 - k);
//    return v;
    return (glong) (
            ((i & 0b0000000000000000000000000000000000000000000000000000000000000001) >> 0) << 63 |
            ((i & 0b0000000000000000000000000000000000000000000000000000000000000010) >> 1) << 62 |
            ((i & 0b0000000000000000000000000000000000000000000000000000000000000100) >> 2) << 61 |
            ((i & 0b0000000000000000000000000000000000000000000000000000000000001000) >> 3) << 60 |
            ((i & 0b0000000000000000000000000000000000000000000000000000000000010000) >> 4) << 59 |
            ((i & 0b0000000000000000000000000000000000000000000000000000000000100000) >> 5) << 58 |
            ((i & 0b0000000000000000000000000000000000000000000000000000000001000000) >> 6) << 57 |
            ((i & 0b0000000000000000000000000000000000000000000000000000000010000000) >> 7) << 56 |
            ((i & 0b0000000000000000000000000000000000000000000000000000000100000000) >> 8) << 55 |
            ((i & 0b0000000000000000000000000000000000000000000000000000001000000000) >> 9) << 54 |
            ((i & 0b0000000000000000000000000000000000000000000000000000010000000000) >> 10) << 53 |
            ((i & 0b0000000000000000000000000000000000000000000000000000100000000000) >> 11) << 52 |
            ((i & 0b0000000000000000000000000000000000000000000000000001000000000000) >> 12) << 51 |
            ((i & 0b0000000000000000000000000000000000000000000000000010000000000000) >> 13) << 50 |
            ((i & 0b0000000000000000000000000000000000000000000000000100000000000000) >> 14) << 49 |
            ((i & 0b0000000000000000000000000000000000000000000000001000000000000000) >> 15) << 48 |
            ((i & 0b0000000000000000000000000000000000000000000000010000000000000000) >> 16) << 47 |
            ((i & 0b0000000000000000000000000000000000000000000000100000000000000000) >> 17) << 46 |
            ((i & 0b0000000000000000000000000000000000000000000001000000000000000000) >> 18) << 45 |
            ((i & 0b0000000000000000000000000000000000000000000010000000000000000000) >> 19) << 44 |
            ((i & 0b0000000000000000000000000000000000000000000100000000000000000000) >> 20) << 43 |
            ((i & 0b0000000000000000000000000000000000000000001000000000000000000000) >> 21) << 42 |
            ((i & 0b0000000000000000000000000000000000000000010000000000000000000000) >> 22) << 41 |
            ((i & 0b0000000000000000000000000000000000000000100000000000000000000000) >> 23) << 40 |
            ((i & 0b0000000000000000000000000000000000000001000000000000000000000000) >> 24) << 39 |
            ((i & 0b0000000000000000000000000000000000000010000000000000000000000000) >> 25) << 38 |
            ((i & 0b0000000000000000000000000000000000000100000000000000000000000000) >> 26) << 37 |
            ((i & 0b0000000000000000000000000000000000001000000000000000000000000000) >> 27) << 36 |
            ((i & 0b0000000000000000000000000000000000010000000000000000000000000000) >> 28) << 35 |
            ((i & 0b0000000000000000000000000000000000100000000000000000000000000000) >> 29) << 34 |
            ((i & 0b0000000000000000000000000000000001000000000000000000000000000000) >> 30) << 33 |
            ((i & 0b0000000000000000000000000000000010000000000000000000000000000000) >> 31) << 32 |
            ((i & 0b0000000000000000000000000000000100000000000000000000000000000000) >> 32) << 31 |
            ((i & 0b0000000000000000000000000000001000000000000000000000000000000000) >> 33) << 30 |
            ((i & 0b0000000000000000000000000000010000000000000000000000000000000000) >> 34) << 29 |
            ((i & 0b0000000000000000000000000000100000000000000000000000000000000000) >> 35) << 28 |
            ((i & 0b0000000000000000000000000001000000000000000000000000000000000000) >> 36) << 27 |
            ((i & 0b0000000000000000000000000010000000000000000000000000000000000000) >> 37) << 26 |
            ((i & 0b0000000000000000000000000100000000000000000000000000000000000000) >> 38) << 25 |
            ((i & 0b0000000000000000000000001000000000000000000000000000000000000000) >> 39) << 24 |
            ((i & 0b0000000000000000000000010000000000000000000000000000000000000000) >> 40) << 23 |
            ((i & 0b0000000000000000000000100000000000000000000000000000000000000000) >> 41) << 22 |
            ((i & 0b0000000000000000000001000000000000000000000000000000000000000000) >> 42) << 21 |
            ((i & 0b0000000000000000000010000000000000000000000000000000000000000000) >> 43) << 20 |
            ((i & 0b0000000000000000000100000000000000000000000000000000000000000000) >> 44) << 19 |
            ((i & 0b0000000000000000001000000000000000000000000000000000000000000000) >> 45) << 18 |
            ((i & 0b0000000000000000010000000000000000000000000000000000000000000000) >> 46) << 17 |
            ((i & 0b0000000000000000100000000000000000000000000000000000000000000000) >> 47) << 16 |
            ((i & 0b0000000000000001000000000000000000000000000000000000000000000000) >> 48) << 15 |
            ((i & 0b0000000000000010000000000000000000000000000000000000000000000000) >> 49) << 14 |
            ((i & 0b0000000000000100000000000000000000000000000000000000000000000000) >> 50) << 13 |
            ((i & 0b0000000000001000000000000000000000000000000000000000000000000000) >> 51) << 12 |
            ((i & 0b0000000000010000000000000000000000000000000000000000000000000000) >> 52) << 11 |
            ((i & 0b0000000000100000000000000000000000000000000000000000000000000000) >> 53) << 10 |
            ((i & 0b0000000001000000000000000000000000000000000000000000000000000000) >> 54) << 9 |
            ((i & 0b0000000010000000000000000000000000000000000000000000000000000000) >> 55) << 8 |
            ((i & 0b0000000100000000000000000000000000000000000000000000000000000000) >> 56) << 7 |
            ((i & 0b0000001000000000000000000000000000000000000000000000000000000000) >> 57) << 6 |
            ((i & 0b0000010000000000000000000000000000000000000000000000000000000000) >> 58) << 5 |
            ((i & 0b0000100000000000000000000000000000000000000000000000000000000000) >> 59) << 4 |
            ((i & 0b0001000000000000000000000000000000000000000000000000000000000000) >> 60) << 3 |
            ((i & 0b0010000000000000000000000000000000000000000000000000000000000000) >> 61) << 2 |
            ((i & 0b0100000000000000000000000000000000000000000000000000000000000000) >> 62) << 1 |
            ((i & 0b1000000000000000000000000000000000000000000000000000000000000000) >> 63) << 0
    );
}

glong Long::reverseBytes(glong i) {
    return (glong) (
            ((i & 0b0000000000000000000000000000000000000000000000000000000011111111) >> 0) << 56 |
            ((i & 0b0000000000000000000000000000000000000000000000001111111100000000) >> 8) << 48 |
            ((i & 0b0000000000000000000000000000000000000000111111110000000000000000) >> 16) << 40 |
            ((i & 0b0000000000000000000000000000000011111111000000000000000000000000) >> 24) << 32 |
            ((i & 0b0000000000000000000000001111111100000000000000000000000000000000) >> 32) << 24 |
            ((i & 0b0000000000000000111111110000000000000000000000000000000000000000) >> 40) << 16 |
            ((i & 0b0000000011111111000000000000000000000000000000000000000000000000) >> 48) << 8 |
            ((i & 0b1111111100000000000000000000000000000000000000000000000000000000) >> 56) << 0
    );
}

glong Long::rotateLeft(glong i, gint distance) {
    distance = distance & 0x3f;
    return shiftLeft(i, distance) | shiftRight(i & (shiftLeft(1, 64 - distance) - 1), 63 - distance);
}

glong Long::rotateRight(glong i, gint distance) {
    distance = distance & 0x3F;
    return shiftRight(i, distance) | shiftLeft(i & (shiftLeft(1, distance + 1) - 1), 63 - distance);
}

glong Long::shiftLeft(glong i, gint distance) {
    if (distance < 0) {
        distance = -distance;
        if (distance > 63)
            return 0;
        return (glong) ((i & ~0ULL) >> distance);
    } else {
        if (distance > 63)
            return 0;
        return (glong) ((i & ~0ULL) << distance);
    }
}

glong Long::shiftRight(glong i, gint distance) {
    if (distance < 0) {
        distance = -distance;
        if (distance > 63)
            return 0;
        return (glong) ((i & ~0ULL) << distance);
    } else {
        if (distance > 63)
            return 0;
        return (glong) ((i & ~0ULL) >> distance);
    }
}

gint Long::signum(glong i) {
    return i < 0 ? -1 : i > 0 ? 1 : 0;
}

gint Long::leadingZeros(glong i) {
    gint v = 0;
    if (i < 0)
        return 0;
    if (i > (1ULL << 32)) {
        v = v + 32;
        i = i >> 32;
    }
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
    return 64 - v;
}

gint Long::trailingZeros(glong i) {
    gint v = 0;
    if (i < 0)
        i = -i;
    while (i & 0b00000000000000000000000000000001) {
        i = shiftRight(i, 1);
        v = v + 1;
    }
    return v;
}

glong Long::hash() const {
    return hash(value);
}

glong Long::hash(glong i) {
    return i;
}

String Long::toBinaryString(glong i) {
    return toUnsignedString(i, 2);
}

glong Long::parseLong(const String &str) {
    return parseLong(str, 10);
}

glong Long::parseUnsignedLong(const String &str) {
    return parseUnsignedLong(str, 10);
}

glong Long::parseLong(const String &str, gint base) {
    gint length = str.length();
    if (36 < base || base < 2)
        throw ValueError("Invalid conversion base: " + Integer::toString(base));
    if (length == 0)
        throw ValueError("Parse failed for input \"\" with base " + Integer::toString(base));
    gint sign = 0;
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

glong Long::parseUnsignedLong(const String &str, gint base) {
    gint length = str.length();
    if (36 < base || base < 2)
        throw ValueError("Invalid conversion base: " + Integer::toString(base));
    if (length == 0)
        throw ValueError("Parse failed for input \"\" with base " + Integer::toString(base));
    gchar c = str.charAt(0);
    if (c == '-')
        throw ValueError("Parse failed: Minus sign on input \"" + str + "\".");
    if (length <= 12 || base == 10 && length <= 18)
        return parseLong(str, base);
    else {
        glong result = 0;
        gint digit;
        for (gint i = c == '+' ? 1 : 0; i < length; ++i) {
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
            glong old = result;
            result = result * base + digit;
            if (0 < result && result < old || old < result && result < 0 || 0 < result && old < 0)
                throw ValueError("Value out of range for input \"" + str + "\" with base " + Integer::toString(base));
        }
        return result;
    }
}

Long Long::valueOf(const String &str) {
    return valueOf(str, 10);
}

Long Long::valueOf(const String &str, gint base) {
    return valueOf(parseLong(str, base));
}

String Long::toHexString(glong i) {
    return toString(i, 16);
}

String Long::toOctalString(glong i) {
    return toString(i, 8);
}
