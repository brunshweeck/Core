//
// Created by brunshweeck on 2023/02/19.
//

#include "Double.h"

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

Double::operator gdouble &() {
    return value;
}
