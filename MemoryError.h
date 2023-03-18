//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_MEMORY_ERROR_H
#define CORE_MEMORY_ERROR_H


#include "Error.h"

/**
 * Thrown to indicate allocation error or memory address access error
 */
class MemoryError : public Error {
public:
    /**
     * Construct new instance of Memory error
     */
    MemoryError() : Error("Out of memory") {}

    /**
     * Construct new instance of Memory error
     * \param message description message
     */
    CORE_EXPLICIT MemoryError(String message) : Error((String &&) message) {}

    /**
     * Return copy of this object
     */
    Object &clone() const override;
};


#endif //CORE_MEMORY_ERROR_H
