//
// Created by brunshweeck on 26/02/2023.
//

#include "OverflowError.h"
#include "../String.h"
#include "MemoryAllocationError.h"

OverflowError::OverflowError() {}

String OverflowError::message() const {
    return "Overflow Error";
}

Object &OverflowError::clone() const {
    try {
        return *new OverflowError();
    }catch(...) {
        throw MemoryAllocationError();
    }
}
