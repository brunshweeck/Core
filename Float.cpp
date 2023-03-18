//
// Created by brunshweeck on 2023/02/19.
//

#include "Float.h"
#include "String.h"
#include "ValueError.h"

CORE_FAST static gint S_MASK = (gint) 0b10000000000000000000000000000000;
CORE_FAST static gint E_MASK = (gint) 0b01111111100000000000000000000000;
CORE_FAST static gint M_MASK = (gint) 0b00000000011111111111111111111111;

static_assert((S_MASK | E_MASK | M_MASK) == ~0, "This Compiler is Not Supported");

gint Float::intValue() const {
    return (gint) value;
}

glong Float::longValue() const {
    return (i64) value;
}

gfloat Float::floatValue() const {
    return (gfloat) value;
}

gdouble Float::doubleValue() const {
    return (f64) value;
}

gbool Float::equals(const Object &obj) const {
    Float const *f = dynamic_cast<Float const *>(&obj);
    if (!f) return false;
    return value == f->value;
}

gint Float::compareTo(const Float &i) const {
    return compare(value, i.value);
}

Float::operator gfloat() const {
    return value;
}

gint Float::compare(gfloat x, gfloat y) {
    return x > y ? 1 :
           x < y ? -1 : 0;
}

Object &Float::clone() const {
    Float *f;
    try { f = new Float(value); } catch (...) {}
    return *f;
}

Float Float::valueOf(gfloat f) {
    return f;
}

gbool Float::isInfinite() const {
    return isInfinite(value);
}

gbool Float::isFinite() const {
    return isFinite(value);
}

gbool Float::isNaN() const {
    return isNaN(value);
}

gbool Float::isInfinite(gfloat v) {
    gint i = toIntBits(v);
    return (i & E_MASK) == E_MASK && (i & M_MASK) == 0;
}

gbool Float::isFinite(gfloat v) {
    gint i = toIntBits(v);
    return (i & E_MASK) != E_MASK;
}

gbool Float::isNaN(gfloat v) {
    return v != v;
}

gint Float::toIntBits(gfloat v) {
    if(isNaN(v))
        return 0x7fc00000;
    gfloat *f = &v;
    gint *i = (gint *) f;
    return *i;
}

gfloat Float::fromIntBits(gint v) {
    gint *i = &v;
    gfloat *f = (gfloat *) i;
    return *f;
}

gfloat const Float::INF = Float::fromIntBits(E_MASK);

gfloat const Float::NAN = Float::fromIntBits(E_MASK | 0b00000000010000000000000000000000);

Float::operator gfloat &() {
    return value;
}

glong Float::hash() const {
    return hash(value);
}

glong Float::hash(gfloat f) {
    return toIntBits(f);
}

Float Float::valueOf(const String &str) {
    return valueOf(parseFloat(str));
}

gfloat Float::parseFloat(const String &str) {
    gint sign = 1;
    gint i = 0;
    gint length = str.length();
    gchar c;
    try {
        c = str.charAt(0);
        if (c == '+') {
            sign = 1;
            i = 1;
            c = str.charAt(1);
        } else if (c == '-') {
            sign = -1;
            i = 1;
            c = str.charAt(1);
        }
    } catch (...) {}
    if (i < length) {
        if ((c == 'n' || c == 'N') && i + 3 == length) {
            c = str.charAt(i + 1);
            if (c == 'a' || c == 'A') {
                c = str.charAt(i + 2);
                if (c == 'n' || c == 'N')
                    return NAN;
            }
        } else if ((c == 'i' || c == 'I') && i + 2 < length) {
            c = str.charAt(i + 1);
            if (c == 'n' || c == 'N') {
                c = str.charAt(i + 2);
                if (c == 'f' || c == 'F') {
                    if (i + 3 == length)
                        return INF * (gfloat) sign;
                    else if (i + 8 == length) {
                        gchar d = str.charAt(i + 3);
                        gchar e = str.charAt(i + 4);
                        gchar f = str.charAt(i + 5);
                        gchar g = str.charAt(i + 6);
                        gchar h = str.charAt(i + 7);
                        if ((d == 'i' || d == 'I') && (e == 'n' || e == 'N') && (f == 'i' || f == 'I') &&
                            (g == 't' || g == 'T') && (h == 'y' || h == 'Y'))
                            return INF * (gfloat) sign;
                    }
                }
            }
        } else if ('0' <= c && c <= '9' || c == '.') {
            gint base = 10;
            if (c == '0' && i + 2 < length) {
                gchar d = str.charAt(i + 1);
                if (d == 'x' || d == 'X') {
                    // hexadecimal
                    base = 16;
                }
            }
            if (base == 10) {
                // decimal parser
                gfloat result = 0;
                gbool isInteger = true;
                gbool hasExponent = false;
                gint exponent = 0;
                gint sign2 = 1;
                gint digit = 0;
                for (; i < length && digit >= 0; ++i) {
                    if (c == '.') {
                        isInteger = false;
                        break;
                    } else if (c == 'e' || c == 'E') {
                        hasExponent = true;
                        break;
                    } else if ('0' <= c && c <= '9') {
                        digit = c - 48;
                        result = result * 10 + (gfloat) digit;
                        if (i + 1 < length)
                            c = str.charAt(i + 1);
                    } else
                        digit = -1;
                }
                if (digit >= 0) {
                    if (!isInteger) {
                        i = i + 1;
                        gfloat pow = 10.0f;
                        for (; i < length && digit >= 0; ++i) {
                            c = str.charAt(i);
                            if (c == 'e' || c == 'E') {
                                hasExponent = true;
                                break;
                            } else if ('0' <= c && c <= '9') {
                                digit = c - 48;
                                result = result + (gfloat) digit / pow;
                                pow = pow * 10.0f;
                            } else {
                                digit = -1;
                            }
                        }
                    }
                    if (hasExponent && i + 2 < length) {
                        i = i + 1;
                        c = str.charAt(i);
                        if (c == '+') {
                            sign = 1;
                            i = i + 1;
                        } else if (c == '-') {
                            sign = -1;
                            i = i + 1;
                        }
                        for (; i < length && digit >= 0; ++i) {
                            c = str.charAt(i);
                            if ('0' <= c && c <= '9') {
                                digit = c - 48;
                                if (exponent < 5000)
                                    exponent = exponent * base + digit;
                            } else {
                                digit = -1;
                            }
                        }
                    }
                }
                if (digit >= 0) {
                    result = result * (gfloat) sign;
                    return !hasExponent ? result : _x10(result, sign2 * exponent);
                }
            }
            if (base == 16) {
                // hexadecimal parser
            }
        }
    }
    throw ValueError("Parse failed for input \"" + str + "\".");
}

gfloat Float::_x10(gfloat result, gint pow) {
    if (isNaN(result))
        return NAN;
    if (isInfinite(result))
        return result;
    if (result == 0)
        return result;
    if (pow >= 40)
        return (gfloat) signum(result) * INF;
    if (pow <= -46)
        return (gfloat) signum(result) * 0.0f;
    if (pow == 1)
        return result * 1.0e+001f;
    if (pow == -1)
        return result * 1.0e-001f;
    if (pow >= 10)
        return result * 1.0e+010f * _x10(result, pow - 10);
    if (pow >= 2)
        return result * 1.0e+002f * _x10(result, pow - 2);
    if (pow <= -10)
        return result * 1.0e-010f * _x10(result, pow + 10);
    if (pow <= -2)
        return result * 1.0e-002f * _x10(result, pow + 2);
    return result;
}

gint Float::signum(gfloat f) {
    if (f > 0)
        return 1;
    else if (f < 0)
        return -1;
    gint i = toIntBits(f);
    if (i & S_MASK)
        return -1;
    return f == 0 ? 0 : 1;
}


