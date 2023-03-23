
#include "Object.h"
#include "Long.h"
#include "MemoryError.h"
#include "StateError.h"
#include "String.h"


gbool Object::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    return false;
}

Object &Object::clone() const {
    if (typeid(*this) == typeid(Object))
        try {
            return *new Object();
        } catch (...) { throw MemoryError(); }
    throw StateError("Unsupported Operation");
}

String Object::toString() const {
    return "<object at address 0x" + Long::toHexString((glong) this) + ">";
}

gbool Object::operator==(const Object &obj) const {
    return equals(obj);
}
