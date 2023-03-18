//
// Created by brunshweeck on 16/03/2023.
//

#include "KeyError.h"
#include "MemoryError.h"

Object &KeyError::clone() const {
    try { return *new KeyError(*this); } catch (...) { throw MemoryError(); }
}

