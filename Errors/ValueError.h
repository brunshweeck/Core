//
// Created by brunshweeck on 26/02/2023.
//

#ifndef CORE_VALUE_ERROR_H
#define CORE_VALUE_ERROR_H


#include "Error.h"
#include "../String.h"

class ValueError: public Error {
public:
    /**
     * Construct new instance of this type with details message
     * \param message details message
     */
    CORE_EXPLICIT ValueError(const String &message);

    /**
     * Return detail message
     */
    String message() const override;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

private:
    String _message;
};


#endif //CORE_VALUE_ERROR_H
