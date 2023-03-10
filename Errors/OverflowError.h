//
// Created by brunshweeck on 26/02/2023.
//

#ifndef CORE_OVERFLOW_ERROR_H
#define CORE_OVERFLOW_ERROR_H


#include "Error.h"

class OverflowError : public Error {
private:
    CORE_EXPLICIT OverflowError();

public:

    String message() const override;

    Object &clone() const override;

    static OverflowError INSTANCE;
};


#endif //CORE_OVERFLOW_ERROR_H
