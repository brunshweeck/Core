
#include "Object.h"
#include "String.h"
#include "MemoryError.h"
#include "Long.h"

gbool Object::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    return false;
}

Object &Object::clone() const {
    try { return *new Object(); } catch (...) { throw MemoryError(); }
}

String Object::toString() const {
    return "<object at address 0x"+ Long::toHexString((glong) this) + ">";
}

gbool Object::operator==(const Object &obj) const {
    return equals(obj);
}

gbool Object::operator!=(const Object &obj) const {
    return !equals(obj);
}

