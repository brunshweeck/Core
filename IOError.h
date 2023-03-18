//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_IOERROR_H
#define CORE_IOERROR_H


#include "Error.h"

/**
 * Thrown to indicate input/output error
 */
class IOError : public Error {
public:
    /**
     * Construct new instance of IOError
     */
    IOError() {};

    /**
     * Construct new instance of IOError
     * \param message description message
     */
    CORE_EXPLICIT IOError(String message) : Error((String &&) message) {}

    /**
     * Return copy of this object
     */
    Object &clone() const override;
};


#endif //CORE_IOERROR_H
