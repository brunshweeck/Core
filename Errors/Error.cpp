//
// Created by brunshweeck on 25/02/2023.
//

#include "Error.h"
#include "../String.h"
#include "MemoryAllocationError.h"

static char CURRENT_MESSAGE[4096] = {};

const char *Error::what() const noexcept {
    String msg = message();
    if (msg.isBlank())
        return "";
    CharArray chars = msg.chars();
    if(msg.isAscii()){
        int i;
        for (i = 0; i < chars.length() && i < 4096; ++i) {
            CURRENT_MESSAGE[i] = (char) chars.get(i);
            if(CURRENT_MESSAGE[i] == 0)
                CURRENT_MESSAGE[i] = '?';
        }
        CURRENT_MESSAGE[i] = 0;
    }else {
        CharBuffer buffer = (CharBuffer) chars;
        ByteBuffer buffer1 = UTF8::INSTANCE
        .onUnmapped(Charset::ErrorAction::IGNORE)
        .onMalformed(Charset::ErrorAction::REPLACE)
        .encode(buffer);
        gint i = 0;
        while(buffer1.hasRemaining() && i < 4096){
            CURRENT_MESSAGE[i] = buffer1.get();
            if(CURRENT_MESSAGE[i] == 0)
                CURRENT_MESSAGE[i] = '?';
            i = i + 1;
        }
        CURRENT_MESSAGE[i] = 0;
    }
    return CURRENT_MESSAGE;
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
