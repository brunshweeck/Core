//
// Created by brunshweeck on 2023/3/12.
//

#include "CastError.h"

CastError::CastError() : Error() {}

gbool CastError::equals(const Object &obj) const {
    if(this == &obj)
        return true;
    if(!Class<CastError>::hasInstance(obj))
        return false;
    CastError const& error = (CastError const&) obj;
    return message() == error.message();
}

Object &CastError::clone() const {
    try { return *new CastError(); } catch (...) { throw 1; }
}

String CastError::toString() const {
    return "CastError";
}
