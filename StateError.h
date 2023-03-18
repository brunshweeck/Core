//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_STATE_ERROR_H
#define CORE_STATE_ERROR_H


#include "Error.h"

class StateError : public Error {
public:
    StateError() {};

    CORE_EXPLICIT StateError(String message) : Error((String &&) message) {};

    Object &clone() const override;
};


#endif //CORE_STATE_ERROR_H
