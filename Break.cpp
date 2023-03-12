//
// Created by brunshweeck on 2023/3/12.
//

#include "Break.h"

Break::Break(): Error() {}

const String &Break::message() const {
    return Error::message();
}

gbool Break::equals(const Object &obj) const {
    return Class<Break>::hasInstance(obj);
}

Object &Break::clone() const {
    static Break aBreak{};
    return aBreak;
}

String Break::toString() const {
    return "Break";
}
