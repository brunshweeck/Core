//
// Created by brunshweeck on 2023/3/12.
//

#include "MemoryError.h"

MemoryError::MemoryError() : Error("Out of memory") {}

MemoryError::MemoryError(const String &message) : Error(message) {}

const String &MemoryError::message() const {
    return Error::message();
}

gbool MemoryError::equals(const Object &obj) const {
    if(this == &obj)
        return true;
    if(!Class<MemoryError>::hasInstance(obj))
        return false;
    MemoryError const& error = (MemoryError const&) obj;
    return message() == error.message();
}

Object &MemoryError::clone() const {
    try { return *new MemoryError(message()); } catch (...) { throw MemoryError(); }
}

String MemoryError::toString() const {
    if(message().isEmpty())
        return "MemoryError";
    return "MemoryError: " + message();
}
