//
// Created by brunshweeck on 02/03/2023.
//

#include "CastError.h"
#include "MemoryAllocationError.h"

CastError::CastError(const String &message) : _message(message) {}

String CastError::message() const {
    return _message;
}

Object &CastError::clone() const {
    try {
        return *new CastError(_message);
    } catch (...) {
        throw MemoryAllocationError();
    }
}

void CastError::set(const Object &obj) {
    if (this == &obj)
        return;
    if (!dynamic_cast<CastError const *>(&obj))
        throw CastError();
    _message = ((CastError const &) obj)._message;
}
