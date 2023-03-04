//
// Created by brunshweeck on 2023/02/19.
//

#include "Float.h"

CORE_FAST static i32 S_MASK = (i32) 0b10000000000000000000000000000000;
CORE_FAST static i32 E_MASK = (i32) 0b01111111100000000000000000000000;
CORE_FAST static i32 M_MASK = (i32) 0b00000000011111111111111111111111;

static_assert((S_MASK | E_MASK | M_MASK) == ~0, "This Compiler is Not Supported");

Float::Float() : Float(0.0f) {}

Float::Float(f32 v) : value(v) {}

gint Float::intValue() const {
    return (i32) value;
}

glong Float::longValue() const {
    return (i64) value;
}

gfloat Float::floatValue() const {
    return (f32) value;
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

gint Float::compare(f32 x, f32 y) {
    return x > y ? 1 :
           x < y ? -1 : 0;
}

Object &Float::clone() const {
    Float *f;
    try { f = new Float(value); } catch (...) {}
    return *f;
}

Float Float::valueOf(f32 f) {
    return f;
}

void Float::set(const Object &obj) {
    Float const *f = dynamic_cast<Float const *>(&obj);
    if (!f) {}
    value = f->value;
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

gbool Float::isInfinite(f32 v) {
    i32 i = toIntBits(v);
    return (i & E_MASK) == E_MASK && (i & M_MASK) == 0;
}

gbool Float::isFinite(f32 v) {
    i32 i = toIntBits(v);
    return (i & E_MASK) != E_MASK;
}

gbool Float::isNaN(f32 v) {
    i32 i = toIntBits(v);
    return (i & E_MASK) == E_MASK && (i & M_MASK) != 0;
}

i32 Float::toIntBits(f32 v) {
    f32 *f = &v;
    i32 *i = (i32 *) f;
    return *i;
}

f32 Float::fromIntBits(i32 v) {
    i32 *i = &v;
    f32 *f = (f32 *) i;
    return *f;
}

f32 const Float::INF = Float::fromIntBits(E_MASK);

f32 const Float::NAN = Float::fromIntBits(E_MASK | 0b00000000010000000000000000000000);

Float::operator gfloat &() {
    return value;
}

glong Float::hash() const {
    return hash(value);
}

glong Float::hash(gfloat f) {
    return toIntBits(f);
}