//
// Created by brunshweeck on 2023/3/12.
//

#include "ValueError.h"
#include "MemoryError.h"

ValueError::ValueError() : Error() {}

ValueError::ValueError(const String &message) : Error(message) {}

const String &ValueError::message() const {
    return Error::message();
}

gbool ValueError::equals(const Object &obj) const {
    if(this == &obj)
        return true;
    if(!Class<ValueError>::hasInstance(obj))
        return false;
    ValueError const& error = (ValueError const&) obj;
    return message() == error.message();
}

Object &ValueError::clone() const {
    try { return *new ValueError(message()); } catch (...) { throw MemoryError(); }
}

String ValueError::toString() const {
    if(message().isEmpty())
        return "ValueError";
    return "ValueError: " + message();
}
