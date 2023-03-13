//
// Created by brunshweeck on 2023/3/12.
//

#include "CodingError.h"
#include "MemoryError.h"
#include "Integer.h"

CodingError::CodingError() : IOError() {}

CodingError::CodingError(const String &message) : IOError(message) {}

const String &CodingError::message() const {
    return IOError::message();
}

gbool CodingError::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!Class<CodingError>::hasInstance(obj))
        return false;
    CodingError const &error = (CodingError const &) obj;
    return message() == error.message();
}

Object &CodingError::clone() const {
    try { return *new CodingError(message()); } catch (...) { throw MemoryError(); }
}

String CodingError::toString() const {
    if (message().isEmpty())
        return "CodingError";
    return "CodingError: " + message();
}

CodingError CodingError::underflow() {
    return CodingError("Buffer underflow");
}

CodingError CodingError::overflow() {
    return CodingError("Buffer overflow");
}

CodingError CodingError::malformed(gint length) {
    if (length <= 0)
        return CodingError("Malformed character input");
    return CodingError("Malformed character input from length " + Integer::toString(length));
}

CodingError CodingError::unmappable(gint length) {
    if (length <= 0)
        return CodingError("Unmappable character input");
    return CodingError("Unmappable character input from length " + Integer::toString(length));
}
