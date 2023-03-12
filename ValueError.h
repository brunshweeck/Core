//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_VALUE_ERROR_H
#define CORE_VALUE_ERROR_H


#include "Error.h"

class ValueError: public Error {
public:
    ValueError();

    CORE_EXPLICIT ValueError(const String &message);

    const String &message() const override;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

    String toString() const override;
};


#endif //CORE_VALUE_ERROR_H
