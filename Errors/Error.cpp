//
// Created by brunshweeck on 25/02/2023.
//

#include "Error.h"
#include "../String.h"
#include "MemoryAllocationError.h"

static gbyte CURRENT_MESSAGE[4096] = {};

const char *Error::what() const noexcept {
    String msg = message();
    if (msg.isBlank())
        return "";
    gint i = msg.bytes(CURRENT_MESSAGE, 4096, 0, msg.length() - 1);
    CURRENT_MESSAGE[i] = 0;
    return (char *) CURRENT_MESSAGE;
}

gbool Error::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!dynamic_cast<Error const *>(&obj))
        return false;
    Error const &error = (const Error &) obj;
    return error.message() == message();
}

Object &Error::clone() const {
    try {
        what();
        return *new Error(*this);
    } catch (...) {
        throw MemoryAllocationError();
    }
}

void Error::set(const Object &obj) {

}

String Error::message() const {
    return (char *) CURRENT_MESSAGE + 0;
}

Error::Error() CORE_NOTHROW = default;
