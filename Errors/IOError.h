//
// Created by brunshweeck on 05/03/2023.
//

#ifndef CORE_IO_ERROR_H
#define CORE_IO_ERROR_H


#include "Error.h"
#include "../String.h"

class IOError: public Error {
public:
    CORE_EXPLICIT IOError(const String &message = "");

private:
    String _message;
};


#endif //CORE_IO_ERROR_H
