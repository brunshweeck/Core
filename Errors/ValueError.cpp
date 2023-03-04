//
// Created by brunshweeck on 26/02/2023.
//

#include "ValueError.h"
#include "MemoryAllocationError.h"

ValueError::ValueError(const String &message) : _message(message) {}

String ValueError::message() const {
    return _message;
}

gbool ValueError::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!dynamic_cast<ValueError const *>(&obj))
        return false;
    return _message.equals(((ValueError const &) obj)._message);
}

Object &ValueError::clone() const {
    try {
        return *new ValueError(_message);
    }catch (...) {
        throw MemoryAllocationError();
    }
}
