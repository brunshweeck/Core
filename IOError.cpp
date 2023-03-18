//
// Created by brunshweeck on 2023/3/12.
//

#include "IOError.h"
#include "MemoryError.h"

Object &IOError::clone() const {
    try { return *new IOError(*this); } catch (...) { throw MemoryError(); }
}
