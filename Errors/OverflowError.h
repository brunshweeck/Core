//
// Created by brunshweeck on 26/02/2023.
//

#ifndef CORE_OVERFLOW_ERROR_H
#define CORE_OVERFLOW_ERROR_H


#include "Error.h"

class OverflowError: public Error {
public:
    CORE_EXPLICIT OverflowError();

    String message() const override;

    Object &clone() const override;
};


#endif //CORE_OVERFLOW_ERROR_H
