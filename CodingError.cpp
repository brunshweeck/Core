//
// Created by brunshweeck on 2023/3/12.
//

#include "CodingError.h"
#include "MemoryError.h"
#include "Integer.h"

Object &CodingError::clone() const {
    try { return *new CodingError(message()); } catch (...) { throw MemoryError(); }
}

CodingError CodingError::underflow() {
    return CodingError("Buffer underflow");
}

CodingError CodingError::overflow() {
    return CodingError("Buffer overflow");
}

CodingError CodingError::malformed(gint length) {
    if (length <= 0)
        return CodingError("Malformed character input");
    return CodingError("Malformed character input from length " + Integer::toString(length));
}

CodingError CodingError::unmappable(gint length) {
    if (length <= 0)
        return CodingError("Unmappable character input");
    return CodingError("Unmappable character input from length " + Integer::toString(length));
}
