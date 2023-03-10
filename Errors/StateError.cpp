//
// Created by brunshweeck on 10/03/2023.
//

#include "StateError.h"
#include "MemoryAllocationError.h"

StateError::StateError(const String &message) : _message(message) {}

String StateError::message() const {
    return _message;
}

gbool StateError::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!dynamic_cast<StateError const *>(&obj))
        return false;
    return _message == ((StateError const &) obj)._message;
}

Object &StateError::clone() const {
    try {
        return *new StateError(_message);
    } catch (...) {
        throw MemoryAllocationError();
    }
}

void StateError::set(const Object &obj) {
    if (this != &obj)
        if (!dynamic_cast<StateError const *>(&obj)) {
            _message = ((StateError const &) obj)._message;
        }
}
