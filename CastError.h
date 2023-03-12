//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_CASTERROR_H
#define CORE_CASTERROR_H


#include "Error.h"

class CastError: public Error {
public:
    CastError();

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

    String toString() const override;
};


#endif //CORE_CASTERROR_H
