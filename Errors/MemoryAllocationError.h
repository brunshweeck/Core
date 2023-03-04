//
// Created by brunshweeck on 25/02/2023.
//

#ifndef CORE_MEMORY_ALLOCATION_ERROR_H
#define CORE_MEMORY_ALLOCATION_ERROR_H


#include "Error.h"

class MemoryAllocationError : public Error {
public:
    /**
     * Construct new Instance
     */
    CORE_EXPLICIT MemoryAllocationError() CORE_NOTHROW;

    /**
     * Return error message
     */
    String message() const override;
};


#endif //CORE_MEMORY_ALLOCATION_ERROR_H
