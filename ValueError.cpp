//
// Created by brunshweeck on 2023/3/12.
//

#include "ValueError.h"
#include "MemoryError.h"

Object &ValueError::clone() const {
    try { return *new ValueError(message()); } catch (...) { throw MemoryError(); }
}
