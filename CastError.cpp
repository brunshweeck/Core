//
// Created by brunshweeck on 2023/3/12.
//

#include "CastError.h"
#include "MemoryError.h"

Object &CastError::clone() const {
    try { return *new CastError(); } catch (...) { throw MemoryError(); }
}

