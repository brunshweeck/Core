//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_STATE_ERROR_H
#define CORE_STATE_ERROR_H


#include "Error.h"

class StateError: public Error {
public:
    StateError();

    explicit StateError(const String &message);

    const String &message() const override;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

    String toString() const override;
};


#endif //CORE_STATE_ERROR_H
