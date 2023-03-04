//
// Created by brunshweeck on 02/03/2023.
//

#ifndef CORE_CASTERROR_H
#define CORE_CASTERROR_H


#include "Error.h"
#include "../String.h"

class CastError: public Error {
public:
    /**
     * Construct new instance of cast error with detail message
     * \param message
     */
    CORE_EXPLICIT CastError(const String &message = "");

    String message() const override;

    Object &clone() const override;

protected:
    void set(const Object &obj) override;

private:
    String _message;
};


#endif //CORE_CASTERROR_H
