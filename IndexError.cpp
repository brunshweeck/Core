//
// Created by brunshweeck on 2023/3/12.
//

#include "IndexError.h"
#include "Integer.h"
#include "Long.h"
#include "MemoryError.h"

IndexError::IndexError(gint index) : ValueError("Index out of range: " + Integer::toString(index)) {}

IndexError::IndexError(glong index) : ValueError("Index out of range: " + Long::toString(index)) {}

IndexError::IndexError(const String &message) : ValueError(message) {}

Object &IndexError::clone() const {
    try { return *new IndexError(message()); } catch (...) { throw MemoryError(); }
}

