//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_CODINGERROR_H
#define CORE_CODINGERROR_H


#include "IOError.h"

/**
 * Thrown to indicate error during character coding
 */
class CodingError : public IOError {
public:
    /**
     * Construct new instance of Coding error
     */
    CodingError() {}

    /**
     * Construct new instance of Coding error
     * \param message description message
     */
    CORE_EXPLICIT CodingError(String message) : IOError((String &&) message) {}

    /**
     * Return copy of this object
     */
    Object &clone() const override;

    /**
     * Construct new coding error with underflow error message
     */
    static CodingError underflow();

    /**
     * Construct new coding error with overflow error message
     */
    static CodingError overflow();

    /**
     * Construct new coding error with malformed error message
     * \param length number of bytes/chars used
     */
    static CodingError malformed(gint length);

    /**
     * Construct new coding error with underflow error message
     * \param length number of bytes/chars used
     */
    static CodingError unmappable(gint length);
};


#endif //CORE_CODINGERROR_H
