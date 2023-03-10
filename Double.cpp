//
// Created by brunshweeck on 2023/02/19.
//

#include "Double.h"
#include "Errors/ValueError.h"

CORE_FAST static i64 S_MASK = (i64) 0b1000000000000000000000000000000000000000000000000000000000000000;

CORE_FAST static i64 E_MASK = (i64) 0b0111111111110000000000000000000000000000000000000000000000000000;

CORE_FAST static i64 M_MASK = (i64) 0b0000000000001111111111111111111111111111111111111111111111111111;

Double::Double() : Double(0.0) {}

Double::Double(f64 v) : value(v) {}

gint Double::intValue() const {
    return (i32) value;
}

glong Double::longValue() const {
    return (i64) value;
}

gfloat Double::floatValue() const {
    return (f32) value;
}

gdouble Double::doubleValue() const {
    return value;
}

gbool Double::isInfinite() const {
    return isInfinite(value);
}

gbool Double::isFinite() const {
    return isFinite(value);
}

gbool Double::isNaN() const {
    return isNaN(value);
}

gbool Double::isInfinite(f64 v) {
    i64 i = toLongBits(v);
    return (i & E_MASK) == E_MASK && (i & M_MASK) == 0;
}

gbool Double::isFinite(f64 v) {
    i64 i = toLongBits(v);
    return (i & E_MASK) != E_MASK;
}

gbool Double::isNaN(f64 v) {
    i64 i = toLongBits(v);
    return (i & E_MASK) == E_MASK && (i & M_MASK) != 0;
}

i64 Double::toLongBits(f64 v) {
    f64 *f = &v;
    i64 *i = (i64 *) f;
    return *i;
}

f64 Double::fromLongBits(i64 v) {
    i64 *i = &v;
    f64 *f = (f64 *) i;
    return *f;
}

gbool Double::equals(const Object &obj) const {
    Double const *d = dynamic_cast<Double const *>(&obj);
    if (!d) return false;
    return compare(value, d->value) == 0;
}

Object &Double::clone() const {
    Double *d;
    try { d = new Double(value); } catch (...) {}
    return *d;
}

gint Double::compareTo(const Double &i) const {
    return compare(value, i.value);
}

Double::operator gdouble() const {
    return value;
}

gint Double::compare(f64 x, f64 y) {
    return x > y ? 1 : x < y ? -1 : 0;
}

Double Double::valueOf(f64 f) {
    return f;
}

void Double::set(const Object &obj) {
    Double const *d = dynamic_cast<Double const *>(&obj);
    if (!d) {}
    value = d->value;
}

f64 const Double::INF = Double::fromLongBits(E_MASK);

f64 const Double::NAN = Double::fromLongBits(
        E_MASK | 0b00000000000001000000000000000000000000000000000000000000000000000);

glong Double::hash() const {
    return hash(value);
}

glong Double::hash(gdouble d) {
    return toLongBits(d);
}

Double Double::valueOf(const String &str) {
    return valueOf(parseDouble(str));
}

gdouble Double::parseDouble(const String &str) {
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
        if ((c == 'n' || c == 'N') && i + 2 < length) {
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
                        return INF * sign;
                    else if (i + 7 < length) {
                        gchar d = str.charAt(i + 3);
                        gchar e = str.charAt(i + 4);
                        gchar f = str.charAt(i + 5);
                        gchar g = str.charAt(i + 6);
                        gchar h = str.charAt(i + 7);
                        if ((d == 'i' || d == 'I') && (e == 'n' || e == 'N') && (f == 'i' || f == 'I') &&
                            (g == 't' || g == 'T') && (h == 'y' || h == 'Y'))
                            return INF * sign;
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
                gdouble result = 0;
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
                        result = result * base + digit;
                        if (i + 1 < length)
                            c = str.charAt(i + 1);
                    } else
                        digit = -1;
                }
                if (digit >= 0) {
                    if (!isInteger) {
                        i = i + 1;
                        gdouble pow = base;
                        for (; i < length && digit >= 0; ++i) {
                            c = str.charAt(i);
                            if (c == 'e' || c == 'E') {
                                hasExponent = true;
                                break;
                            } else if ('0' <= c && c <= '9') {
                                digit = c - 48;
                                result = result + digit / pow;
                                pow = pow * base;
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
                    result = result * sign;
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

gdouble Double::_x10(gdouble result, gint pow) {
    if (isNaN(result))
        return NAN;
    if (isInfinite(result))
        return result;
    if(result == 0)
        return result;
    if (pow >= 310)
        return signum(result) * INF;
    if (pow <= -325)
        return signum(result) * 0.0;
    if(pow == 1)
        return result * 1.0e+001;
    if(pow == -1)
        return result * 1.0e-001;
    if(pow >= 100)
        return result * 1.0e+100 * _x10(result, pow - 100);
    if(pow >= 10)
        return result * 1.0e+010 * _x10(result, pow - 10);
    if(pow >= 2)
        return result * 1.0e+002 * _x10(result, pow - 2);
    if(pow <= -100)
        return result * 1.0e-100 * _x10(result, pow + 100);
    if(pow <= -10)
        return result * 1.0e-010 * _x10(result, pow + 10);
    if(pow <= -2)
        return result * 1.0e-002 * _x10(result, pow + 2);
    return result;
}

gint Double::signum(gdouble f) {
    if(f > 0)
        return 1;
    if( f < 0)
        return -1;
    glong i = toLongBits(f);
    return i & S_MASK ? -1 : 0;
}

Double::operator gdouble &() {
    return value;
}
