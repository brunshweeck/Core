//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_MEMORY_ERROR_H
#define CORE_MEMORY_ERROR_H


#include "Error.h"

class MemoryError: public Error {
public:
    MemoryError();

    CORE_EXPLICIT MemoryError(const String &message);

    const String &message() const override;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

    String toString() const override;
};


#endif //CORE_MEMORY_ERROR_H
