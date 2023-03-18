//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_VALUE_ERROR_H
#define CORE_VALUE_ERROR_H


#include "Error.h"

/**
 * Thrown to indicate illegal argument value
 */
class ValueError : public Error {
public:
    /**
     * Construct new instance of Value error
     */
    ValueError() {}

    /**
     * Construct new instance of Value error
     * \param message description message
     */
    CORE_EXPLICIT ValueError(String message) : Error((String &&) message) {}

    /**
     * Return copy of this object
     */
    Object &clone() const override;
};


#endif //CORE_VALUE_ERROR_H
