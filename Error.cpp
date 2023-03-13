//
// Created by brunshweeck on 2023/3/12.
//

#include "Error.h"
#include "MemoryError.h"
#include "Collections/CharArray.h"
#include "IO/CharBuffer.h"
#include "IO/ByteBuffer.h"
#include "Charset/UTF8.h"

Error::Error() : _message() {}

Error::Error(const String &message) : _message(message) {}

const String &Error::message() const {
    return _message;
}

gbool Error::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!Class<Error>::hasInstance(obj))
        return false;
    Error const &error = (Error const &) obj;
    if (typeid(*this) != typeid(error) && typeid(Error) != typeid(error))
        return false;
    return error.message() == message();
}

Object &Error::clone() const {
    try { return *new Error(message()); } catch (...) { throw MemoryError(); }
}

String Error::toString() const {
    if(message().isEmpty())
        return "Error";
    return "Error: " + message();
}

void Error::set(const Object &obj) {
    if (!Class<Error>::hasInstance(obj)) {}
    Error const &error = (Error const &) obj;
    _message = error.message();
}

const char *Error::what() const noexcept {
    static char buffer[512] = {};
    CharArray chars = toString().chars();
    CharBuffer in = (CharBuffer) chars;
    ByteBuffer out = UTF8::INSTANCE
            .onMalformed(Charset::ErrorAction::REPLACE)
            .onUnmapped(Charset::ErrorAction::REPLACE)
            .encode(in);
    gint i = 0;
    for (char &c: buffer) {
        if (!out.hasRemaining())
            break;
        c = out.get();
        i += 1;
    }
    buffer[i] = 0;
    return buffer;
}
