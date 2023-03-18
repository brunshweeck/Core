//
// Created by brunshweeck on 2023/3/12.
//

#include "StateError.h"
#include "MemoryError.h"

Object &StateError::clone() const {
    try { return *new StateError(message()); } catch (...) { throw MemoryError(); }
}
