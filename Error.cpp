//
// Created by brunshweeck on 2023/3/12.
//

#include "Error.h"
#include "MemoryError.h"
#include "Collections/CharArray.h"
#include "IO/CharBuffer.h"
#include "IO/ByteBuffer.h"
#include "Charset/UTF8.h"

String Error::message() const {
    return _message;
}

gbool Error::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!Class<Error>::hasInstance(obj))
        return false;
    Error const &error = (Error const &) obj;
    if (typeid(*this) != typeid(error))
        return false;
    return error._message == _message;
}

Object &Error::clone() const {
    try { return *new Error(message()); } catch (...) { throw MemoryError(); }
}

String Error::toString() const {
    return "Message: " + message();
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
        if (i < 10)
            c = '\b';
        else if (i < 512)
            if (!out.hasRemaining())
                break;
            else
                c = out.get();
        else
            break;
        i += 1;
    }
    buffer[i] = 0;
    return buffer;
}
