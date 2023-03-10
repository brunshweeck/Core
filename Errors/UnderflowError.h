//
// Created by brunshweeck on 05/03/2023.
//

#ifndef CORE_UNDERFLOW_ERROR_H
#define CORE_UNDERFLOW_ERROR_H


#include "Error.h"

class UnderflowError: public Error {
private:
    CORE_EXPLICIT UnderflowError();

public:
    String message() const override;

    Object &clone() const override;

    static UnderflowError INSTANCE;
};


#endif //CORE_UNDERFLOWERROR_H
