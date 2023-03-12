//
// Created by brunshweeck on 2023/3/12.
//

#include "StateError.h"
#include "MemoryError.h"

StateError::StateError() : Error() {}

StateError::StateError(const String &message) : Error(message) {}

const String &StateError::message() const {
    return Error::message();
}

gbool StateError::equals(const Object &obj) const {
    if(this == &obj)
        return true;
    if(!Class<StateError>::hasInstance(obj))
        return false;
    StateError const& error = (StateError const&) obj;
    return message() == error.message();
}

Object &StateError::clone() const {
    try { return *new StateError(message()); } catch (...) { throw MemoryError(); }
}

String StateError::toString() const {
    if(message().isEmpty())
        return "StateError";
    return "StateError: " + message();
}
