//
// Created by brunshweeck on 25/02/2023.
//

#include "MemoryAllocationError.h"
#include "../String.h"

String MemoryAllocationError::message() const {
    return "Memory Allocation Fail";
}

MemoryAllocationError::MemoryAllocationError() CORE_NOTHROW = default;
