//
// Created by brunshweeck on 2023/3/12.
//

#include "MemoryError.h"

Object &MemoryError::clone() const {
    try { return *new MemoryError(message()); } catch (...) { throw MemoryError(); }
}
