//
// Created by brunshweeck on 2023/02/19.
//

#include "Byte.h"

Byte::Byte() : Byte(0) {}

Byte::Byte(i8 v) : value(v) {}

gint Byte::intValue() const {
    return (i32) value;
}

glong Byte::longValue() const {
    return (i64) value;
}

gfloat Byte::floatValue() const {
    return (f32) value;
}

gdouble Byte::doubleValue() const {
    return (f64) value;
}

gbool Byte::equals(const Object &obj) const {
    Byte const *b = dynamic_cast<Byte const *>(&obj);
    if (!b) return false;
    return value == b->value;
}

Object &Byte::clone() const {
    Byte *b;
    try { b = new Byte(value); } catch (...) {}
    return *b;
}

void Byte::set(const Object &obj) {
    Byte const *b = dynamic_cast<Byte const *>(&obj);
    if (!b) {}
    value = b->value;
}

gint Byte::compareTo(const Byte &i) const {
    return compare(value, i.value);
}

Byte::operator gbyte() const {
    return value;
}

Byte Byte::valueOf(i8 i) {
    return i;
}

gint Byte::compare(i8 x, i8 y) {
    return x > y ? 1 :
           x < y ? -1 : 0;
}

Byte::operator gbyte &() {
    return value;
}

glong Byte::hash() const {
    return hash(value);
}

glong Byte::hash(gbyte b) {
    return b;
}


