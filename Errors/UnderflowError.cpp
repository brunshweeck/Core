//
// Created by brunshweeck on 05/03/2023.
//

#include "UnderflowError.h"
#include "../String.h"

UnderflowError::UnderflowError() {}

String UnderflowError::message() const {
    return "Underflow error";
}

UnderflowError UnderflowError::INSTANCE{};

Object &UnderflowError::clone() const {
    return INSTANCE;
}


