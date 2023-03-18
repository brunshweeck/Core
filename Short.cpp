//
// Created by brunshweeck on 2023/02/19.
//

#include "Short.h"
#include "Integer.h"
#include "String.h"
#include "ValueError.h"

gint Short::intValue() const {
    return (i32) value;
}

glong Short::longValue() const {
    return (i64) value;
}

gfloat Short::floatValue() const {
    return (f32) value;
}

gdouble Short::doubleValue() const {
    return (f64) value;
}

gbool Short::equals(const Object &obj) const {
    if(this == &obj)
        return true;
    if(!Class<Short>::hasInstance(obj))
        return false;
    Short const& aShort = (const Short &) obj;
    return value == aShort.value;
}

Object &Short::clone() const {
    Short *s;
    try { s = new Short(value); } catch (...) {}
    return *s;
}

gint Short::compare(i16 x, i16 y) {
    return x > y ? 1 :
           x < y ? -1 : 0;
}

Short Short::valueOf(i16 i) {
    return i;
}

Short::operator gshort() const {
    return shortValue();
}

gint Short::compareTo(const Short &i) const {
    return compare(value, i.value);
}

Short::operator gshort &() {
    return value;
}

gint Short::toUnsignedInt(i16 i) {
    return i & 0xFFFF;
}

glong Short::toUnsignedLong(i16 i) {
    return i & 0xFFFFLL;
}

i16 Short::reverseBytes(i16 i) {
    return (i16) (
            ((i & 0b0000000011111111) >> 0) << 8 |
            ((i & 0b1111111100000000) >> 8) << 0
    );
}

glong Short::hash() const {
    return hash(value);
}

glong Short::hash(i16 i) {
    return i;
}

gshort Short::parseShort(const String &str, gint base) {
    gint result = Integer::parseInt(str, base);
    if (MAX < result || result < MIN)
        throw ValueError("Value for input \"" + str + "\" with base " + Integer::toString(base));
    return (gshort) result;
}

gshort Short::parseShort(const String &str) {
    return parseShort(str, 10);
}

Short Short::valueOf(const String &str) {
    return valueOf(str, 10);
}

Short Short::valueOf(const String &str, gint base) {
    return valueOf(parseShort(str, base));
}

Short Short::decode(const String &str) {
    gint result = Integer::decode(str);
    if (MAX < result || result < MIN)
        throw ValueError("Value out of range for input \"" + str + "\"");
    return valueOf((gshort) result);
}
