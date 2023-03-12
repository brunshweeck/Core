//
// Created by brunshweeck on 2023/02/19.
//

#include "Number.h"
#include "String.h"
#include "/ValueError.h"
#include "Integer.h"
#include "Byte.h"
#include "Short.h"
#include "Long.h"
#include "Float.h"
#include "Double.h"

CORE_FAST static i32 S_MASK = (i32) 0b10000000000000000000000000000000;
CORE_FAST static i32 E_MASK = (i32) 0b01111111100000000000000000000000;
CORE_FAST static i32 M_MASK = (i32) 0b00000000011111111111111111111111;
CORE_FAST static i64 S_MASK2 = (i64) 0b1000000000000000000000000000000000000000000000000000000000000000;
CORE_FAST static i64 E_MASK2 = (i64) 0b0111111111110000000000000000000000000000000000000000000000000000;
CORE_FAST static i64 M_MASK2 = (i64) 0b0000000000001111111111111111111111111111111111111111111111111111;

gbyte Number::byteValue() const {
    return (gbyte) intValue();
}

gshort Number::shortValue() const {
    return (gshort) intValue();
}

String Number::toString() const {
    return String("Number@").concat(Integer::toUnsignedString(glong(this), 16));
}

gchar NUMBER_CONVERSION_BUFFER[4096] = u"";
gchar DIGIT_NUMBERS[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z'
};

String Integer::toString() const {
    return toString(value);
}

String Integer::toString(gint i) {
    return toString(i, 10);
}

String Integer::toString(gint i, gint base) {
    if (base < 2 || base > 36)
        throw ValueError("invalid conversion base");
    gint v = i < 0 ? -i : i;
    gint index = 4096;
    do {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = DIGIT_NUMBERS[v % base];
        v = v / base;
    } while (v > 0);
    if (i < 0) {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = '-';
    }
    return String(NUMBER_CONVERSION_BUFFER + index, 0, 4096 - index);
}

String Integer::toUnsignedString(gint i) {
    return toUnsignedString(i, 10);
}

String Integer::toUnsignedString(gint i, gint base) {
    if (base < 2 || base > 36)
        throw ValueError("invalid conversion base");
    glong v = Integer::toUnsignedLong(i);
    gint index = 4096;
    do {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = DIGIT_NUMBERS[v % base];
        v = v / base;
    } while (v > 0);
    return String(NUMBER_CONVERSION_BUFFER + index, 0, 4096 - index);
}

String Byte::toString() const {
    return toString(value);
}

String Byte::toString(gbyte i) {
    return toString(i, 10);
}

String Byte::toString(gbyte i, gint base) {
    if (base < 2 || base > 36)
        throw ValueError("invalid conversion base");
    gint v = i < 0 ? -i : i;
    gint index = 4096;
    do {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = DIGIT_NUMBERS[v % base];
        v = v / base;
    } while (v > 0);
    if (i < 0) {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = '-';
    }
    return String(NUMBER_CONVERSION_BUFFER + index, 0, 4096 - index);
}

String Byte::toUnsignedString(gbyte i) {
    return toUnsignedString(i, 10);
}

String Byte::toUnsignedString(gbyte i, gint base) {
    if (base < 2 || base > 36)
        throw ValueError("invalid conversion base");
    glong v = i & 0xFF;
    gint index = 4096;
    do {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = DIGIT_NUMBERS[v % base];
        v = v / base;
    } while (v > 0);
    return String(NUMBER_CONVERSION_BUFFER + index, 0, 4096 - index);
}

String Short::toString() const {
    return toString(value);
}

String Short::toString(gshort i) {
    return toString(i, 10);
}

String Short::toString(gshort i, gint base) {
    if (base < 2 || base > 36)
        throw ValueError("invalid conversion base");
    gint v = i < 0 ? -i : i;
    gint index = 4096;
    do {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = DIGIT_NUMBERS[v % base];
        v = v / base;
    } while (v > 0);
    if (i < 0) {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = '-';
    }
    return String(NUMBER_CONVERSION_BUFFER + index, 0, 4096 - index);
}

String Short::toUnsignedString(gshort i) {
    return toUnsignedString(i, 10);
}

String Short::toUnsignedString(gshort i, gint base) {
    if (base < 2 || base > 36)
        throw ValueError("invalid conversion base");
    glong v = i & 0xFFFF;
    gint index = 4096;
    do {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = DIGIT_NUMBERS[v % base];
        v = v / base;
    } while (v > 0);
    return String(NUMBER_CONVERSION_BUFFER + index, 0, 4096 - index);
}

String Long::toString() const {
    return toString(value);
}

String Long::toString(glong i) {
    return toString(i, 10);
}

String Long::toString(glong i, gint base) {
    if (base < 2 || base > 36)
        throw ValueError("invalid conversion base");
    glong v = i < 0 ? -i : i;
    gint index = 4096;
    do {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = DIGIT_NUMBERS[v % base];
        v = v / base;
    } while (v > 0);
    if (i < 0) {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = '-';
    }
    return String(NUMBER_CONVERSION_BUFFER + index, 0, 4096 - index);
}

String Long::toUnsignedString(glong i) {
    return toUnsignedString(i, 10);
}

String Long::toUnsignedString(glong i, gint base) {
    if (base < 2 || base > 36)
        throw ValueError("invalid conversion base");
    glong v = i;
    gint index = 4096;
    do {
        index -= 1;
        NUMBER_CONVERSION_BUFFER[index] = DIGIT_NUMBERS[(v & 0xFFFFFFFFFFFFFFFF) % base];
        v = (v & 0xFFFFFFFFFFFFFFFF) / base;
    } while (v > 0);
    return String(NUMBER_CONVERSION_BUFFER + index, 0, 4096 - index);
}

String Float::toString() const {
    return toString(value);
}

String Float::toHexString(gfloat f) {
    if (!isFinite(f))
        return toString(f);
    gint bits = toIntBits(f);
    gint i = 0;
    if (bits & S_MASK) {
        f = -f;
        NUMBER_CONVERSION_BUFFER[i] = '-';
        i = i + 1;
    }
    NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[0];
    NUMBER_CONVERSION_BUFFER[i + 1] = 'x';
    i = i + 2;
    if (f == 0.0f) {
        NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[0];
        NUMBER_CONVERSION_BUFFER[i + 1] = '.';
        NUMBER_CONVERSION_BUFFER[i + 2] = DIGIT_NUMBERS[0];
        NUMBER_CONVERSION_BUFFER[i + 3] = 'p';
        NUMBER_CONVERSION_BUFFER[i + 4] = DIGIT_NUMBERS[0];
        NUMBER_CONVERSION_BUFFER[i + 5] = 0;
        i = i + 5;
    } else {
        NUMBER_CONVERSION_BUFFER[i + 0] = f < Float::MIN_NORMAL ? '0' : '1';
        NUMBER_CONVERSION_BUFFER[i + 1] = '.';
        gint mantissa = bits & M_MASK;
        NUMBER_CONVERSION_BUFFER[i + 7] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = mantissa >> 4;
        NUMBER_CONVERSION_BUFFER[i + 6] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = mantissa >> 4;
        NUMBER_CONVERSION_BUFFER[i + 5] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = mantissa >> 4;
        NUMBER_CONVERSION_BUFFER[i + 4] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = mantissa >> 4;
        NUMBER_CONVERSION_BUFFER[i + 3] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = mantissa >> 4;
        NUMBER_CONVERSION_BUFFER[i + 2] = DIGIT_NUMBERS[mantissa & 0xF];
        NUMBER_CONVERSION_BUFFER[i + 8] = 'p';
        i = i + 9;
        if (f < Float::MIN_NORMAL) {
            NUMBER_CONVERSION_BUFFER[i + 0] = '-';
            NUMBER_CONVERSION_BUFFER[i + 1] = DIGIT_NUMBERS[1];
            NUMBER_CONVERSION_BUFFER[i + 2] = DIGIT_NUMBERS[0];
            NUMBER_CONVERSION_BUFFER[i + 3] = DIGIT_NUMBERS[2];
            NUMBER_CONVERSION_BUFFER[i + 4] = DIGIT_NUMBERS[2];
            NUMBER_CONVERSION_BUFFER[i + 5] = 0;
            i = i + 5;
        } else {
            gint exponent = (bits & E_MASK) >> 23;
            exponent = exponent - 127;
            if (exponent < 0) {
                exponent = -exponent;
                NUMBER_CONVERSION_BUFFER[i + 0] = '-';
                i = i + 1;
            }
            if (exponent >= 1000) {
                NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[exponent / 1000];
                i = i + 1;
            }
            if (exponent >= 100) {
                NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[exponent % 1000 / 100];
                i = i + 1;
            }
            if (exponent >= 10) {
                NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[exponent % 100 / 10];
                i = i + 1;
            }
            NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[exponent % 10];
            NUMBER_CONVERSION_BUFFER[i + 1] = 0;
            i = i + 1;
        }
    }
    return String(NUMBER_CONVERSION_BUFFER, 0, i);
}

String Double::toString() const {
    return toString(value);
}

String Double::toHexString(gdouble d) {
    if (!isFinite(d))
        return toString(d);
    glong bits = toLongBits(d);
    gint i = 0;
    if (bits & S_MASK2) {
        d = -d;
        NUMBER_CONVERSION_BUFFER[i] = '-';
        i = i + 1;
    }
    NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[0];
    NUMBER_CONVERSION_BUFFER[i + 1] = 'x';
    i = i + 2;
    if (d == 0.0f) {
        NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[0];
        NUMBER_CONVERSION_BUFFER[i + 1] = '.';
        NUMBER_CONVERSION_BUFFER[i + 2] = DIGIT_NUMBERS[0];
        NUMBER_CONVERSION_BUFFER[i + 3] = 'p';
        NUMBER_CONVERSION_BUFFER[i + 4] = DIGIT_NUMBERS[0];
        NUMBER_CONVERSION_BUFFER[i + 5] = 0;
        i = i + 5;
    } else {
        NUMBER_CONVERSION_BUFFER[i + 0] = d < MIN_NORMAL ? DIGIT_NUMBERS[0] : '1';
        NUMBER_CONVERSION_BUFFER[i + 1] = '.';
        glong mantissa = bits & M_MASK2;
        NUMBER_CONVERSION_BUFFER[i + 14] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 13] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 12] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 11] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 10] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 9] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 8] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 7] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 6] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 5] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 4] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 3] = DIGIT_NUMBERS[mantissa & 0xF];
        mantissa = (glong) ((mantissa & 0xFFFFFFFFFFFFFFFF) >> 4);
        NUMBER_CONVERSION_BUFFER[i + 2] = DIGIT_NUMBERS[mantissa & 0xF];
        NUMBER_CONVERSION_BUFFER[i + 15] = 'p';
        i = i + 16;
        if (d < MIN_NORMAL) {
            NUMBER_CONVERSION_BUFFER[i + 0] = '-';
            NUMBER_CONVERSION_BUFFER[i + 1] = DIGIT_NUMBERS[1];
            NUMBER_CONVERSION_BUFFER[i + 2] = DIGIT_NUMBERS[0];
            NUMBER_CONVERSION_BUFFER[i + 3] = DIGIT_NUMBERS[2];
            NUMBER_CONVERSION_BUFFER[i + 4] = DIGIT_NUMBERS[2];
            NUMBER_CONVERSION_BUFFER[i + 5] = 0;
            i = i + 5;
        } else {
            glong exponent = (bits & E_MASK2) >> (53 - 1);
            exponent = exponent - 1023;
            if (exponent < 0) {
                exponent = -exponent;
                NUMBER_CONVERSION_BUFFER[i + 0] = '-';
                i = i + 1;
            }
            if (exponent >= 1000) {
                NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[exponent / 1000];
                i = i + 1;
            }
            if (exponent >= 100) {
                NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[exponent % 1000 / 100];
                i = i + 1;
            }
            if (exponent >= 10) {
                NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[exponent % 100 / 10];
                i = i + 1;
            }
            NUMBER_CONVERSION_BUFFER[i + 0] = DIGIT_NUMBERS[exponent % 10];
            NUMBER_CONVERSION_BUFFER[i + 1] = 0;
            i = i + 1;
        }
    }
    return String(NUMBER_CONVERSION_BUFFER, 0, i);
}

String Double::toString(gdouble d) {
    if (Double::isNaN(d))
        return "NaN";
    else if (Double::isInfinite(d))
        if (d < 0)
            return "-Infinity";
        else
            return "Infinity";
    else if (d == 0) {
        if (1 / d < 0)
            return "-0.0";
        else
            return "0.0";
    } else {
        gint i = 0;
        if (d < 0) {
            d = -d;
            NUMBER_CONVERSION_BUFFER[i] = '-';
            i = i + 1;
        }
        gint exp = 0;
        gdouble pow = 1;
        if (d >= 1) {
            while (pow * 10 < d) {
                pow = pow * 10;
                exp = exp + 1;
            }
            if (pow > 1.0E8) {
                // scientific
                gbyte digit = (gbyte) (d / pow);
                d = d - digit * pow;
                pow = pow / 10;
                NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[digit];
                NUMBER_CONVERSION_BUFFER[i + 1] = '.';
                i = i + 2;
                if (d == 0) {
                    NUMBER_CONVERSION_BUFFER[i] = '0';
                    i = i + 1;
                } else {
                    gint j = 0;
                    while (j <= 15 && d != 0) {
                        digit = (gbyte) (d / pow);
                        d = d - digit * pow;
                        pow = pow / 10;
                        NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[digit];
                        i = i + 1;
                        j = j + 1;
                    }
                }
                NUMBER_CONVERSION_BUFFER[i] = 'e';
                i = i + 1;
                if (exp >= 100) {
                    NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[exp / 100];
                    i = i + 1;
                }
                if (exp >= 10) {
                    NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[exp % 100 / 10];
                    i = i + 1;
                }
                NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[exp % 10];
                i = i + 1;
                NUMBER_CONVERSION_BUFFER[i] = 0;
                return String(NUMBER_CONVERSION_BUFFER, 0, i);
            } else {
                // NUMBER_CONVERSION_BUFFER
                while (pow >= 1) {
                    gbyte digit = (gbyte) (d / pow);
                    d = d - digit * pow;
                    pow = pow / 10;
                    NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[digit];
                    i = i + 1;
                }
                NUMBER_CONVERSION_BUFFER[i] = '.';
                i = i + 1;
                gbyte digit;
                if (d == 0) {
                    NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[0];
                    i = i + 1;
                } else {
                    gint j = 0;
                    while (j <= 5 && d * 10 > 1) {
                        digit = (gbyte) (d / pow);
                        d = d - digit * pow;
                        pow = pow / 10;
                        NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[digit];
                        i = i + 1;
                        j = j + 1;
                    }
                }
                NUMBER_CONVERSION_BUFFER[i] = 0;
                return String(NUMBER_CONVERSION_BUFFER, 0, i);
            }
        } else {
            gbyte digit;
            while (pow / 10 > d) {
                pow = pow / 10;
                exp = exp + 1;
            }
            if (pow < 1.0E-3) {
                // scientific
                while (pow <= 1) {
                    digit = (gbyte) (d / pow);
                    pow = pow * 10;
                    if (digit != 0)
                        break;
                }
                d = d / pow;
                NUMBER_CONVERSION_BUFFER[i] = (gbyte) DIGIT_NUMBERS[digit];
                NUMBER_CONVERSION_BUFFER[i + 1] = '.';
                i = i + 2;
                if (d == 0) {
                    NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[0];
                    i = i + 1;
                } else {
                    gint j = 0;
                    while (j <= 5) {
                        digit = (gbyte) (d / pow);
                        d = d - digit * pow;
                        pow = pow * 10;
                        NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[digit];
                        i = i + 1;
                        j = j + 1;
                    }
                }
            } else {
                // NUMBER_CONVERSION_BUFFER
                NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[0];
                NUMBER_CONVERSION_BUFFER[i + 1] = '.';
                i = i + 2;
                if (d == 0) {
                    NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[0];
                    i = i + 1;
                } else {
                    gint j = 0;
                    while (j <= 5 && d * 10 > 1) {
                        digit = (gbyte) (d / pow);
                        d = d - digit * pow;
                        pow = pow * 10;
                        NUMBER_CONVERSION_BUFFER[i] = DIGIT_NUMBERS[digit];
                        i = i + 1;
                        j = j + 1;
                    }
                }
            }
            NUMBER_CONVERSION_BUFFER[i] = 0;
            return String(NUMBER_CONVERSION_BUFFER, 0, i);
        }
    }
}

String Float::toString(gfloat f) {
    if ((gfloat) (glong) f == f)
        return Long::toString((glong) f) + ".0";
    return Double::toString(f);
}

