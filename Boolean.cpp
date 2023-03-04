//
// Created by brunshweeck on 2023/2/20.
//

#include "Boolean.h"
#include "String.h"

Boolean::Boolean() : Boolean(false) {}

Boolean::Boolean(gbool v) : value(v) {}

gbool Boolean::equals(const Object &obj) const {
    Boolean const *b = dynamic_cast<Boolean const *>(&obj);
    if (!b) return false;
    return value == b->value;
}

Object &Boolean::clone() const {
    Boolean *b;
    try { b = new Boolean(value); } catch (...) {}
    return *b;
}

void Boolean::set(const Object &obj) {
    Boolean const *b = dynamic_cast<Boolean const *>(&obj);
    if (!b) {}
    value = b->value;
}

gint Boolean::compareTo(const Boolean &b) const {
    return compare(value, b.value);
}

gint Boolean::compare(gbool x, gbool y) {
    return x ? y ? 0 : 1 : y ? -1 : 0;
}

Boolean Boolean::valueOf(gbool b) {
    return b;
}

Boolean::operator gbool() const {
    return value;
}

Boolean::operator gbool &() {
    return value;
}

gbool Boolean::logicalAnd(gbool x, gbool y) {
    return x && y;
}

gbool Boolean::logicalOr(gbool x, gbool y) {
    return x || y;
}

gbool Boolean::logicalXor(gbool x, gbool y) {
    return x == !y;
}

gbool Boolean::booleanValue() const {
    return value;
}

Boolean const Boolean::TRUE = true;

Boolean const Boolean::FALSE = false;

String Boolean::toString() const {
    return value ? "true" : "false";
}
