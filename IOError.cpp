//
// Created by brunshweeck on 2023/3/12.
//

#include "IOError.h"
#include "MemoryError.h"

IOError::IOError() : Error() {}

IOError::IOError(const String &message) : Error(message) {}

const String &IOError::message() const {
    return Error::message();
}

gbool IOError::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!Class<IOError>::hasInstance(obj))
        return false;
    IOError const &error = (IOError const &) obj;
    return message() == error.message();
}

Object &IOError::clone() const {
    try { return *new IOError(message()); } catch (...) { throw MemoryError(); }
}

String IOError::toString() const {
    if (message().isEmpty())
        return "IOError";
    return "IOError: " + message();
}
