//
// Created by brunshweeck on 2023/2/20.
//

#include "Boolean.h"
#include "String.h"
#include "MemoryError.h"

gbool Boolean::equals(const Object &obj) const {
    if (Object::equals(obj))
        return true;
    if (!Class<Boolean>::hasInstance(obj))
        return false;
    Boolean const &boolean = (const Boolean &) obj;
    return value == boolean.value;
}

Object &Boolean::clone() const {
    try { return *new Boolean(value); } catch (...) { throw MemoryError(); }
}

gint Boolean::compareTo(const Boolean &b) const {
    return compare(value, b.value);
}

gint Boolean::compare(gbool x, gbool y) {
    return (gint) x - (gint) y;
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

Boolean const Boolean::TRUE = true;

Boolean const Boolean::FALSE = false;

String Boolean::toString() const {
    return value ? "true" : "false";
}

gbool Boolean::booleanValue() const {
    return value;
}
