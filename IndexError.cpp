//
// Created by brunshweeck on 2023/3/12.
//

#include "IndexError.h"
#include "Integer.h"
#include "Long.h"
#include "MemoryError.h"

IndexError::IndexError() : ValueError("Index out range") {}

IndexError::IndexError(gint index) : ValueError("Index out of range: " + Integer::toString(index)) {}

IndexError::IndexError(glong index) : ValueError("Index out of range: " + Long::toString(index)) {}

IndexError::IndexError(const String &message) : ValueError(message) {}

const String &IndexError::message() const {
    return ValueError::message();
}

gbool IndexError::equals(const Object &obj) const {
    if (this == &obj)
        return true;
    if (!Class<IndexError>::hasInstance(obj))
        return false;
    IndexError const &error = (IndexError const &) obj;
    return message() == error.message();
}

Object &IndexError::clone() const {
    try { return *new IndexError(message()); } catch (...) { throw MemoryError(); }
}

String IndexError::toString() const {
    return "IndexError: " + message();
}

