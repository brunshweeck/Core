//
// Created by brunshweeck on 05/03/2023.
//

#include "CodingError.h"
#include "../Integer.h"

CodingError::CodingError() {}

CodingError CodingError::malformed(gint length) {
    return CodingError("Malformed input of length " + Integer::toUnsignedString(length));
}

CodingError CodingError::unmappable(gint length) {
    return CodingError("Unmappable character input of length " + Integer::toUnsignedString(length));
}

CodingError::CodingError(const String &message) : IOError(message) {}
