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

OverflowError OverflowError::INSTANCE{};

Object &OverflowError::clone() const {
    return INSTANCE;
}
