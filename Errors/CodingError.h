//
// Created by brunshweeck on 05/03/2023.
//

#ifndef CORE_CODINGERROR_H
#define CORE_CODINGERROR_H


#include "IOError.h"

class CodingError : public IOError {
public:
    CORE_EXPLICIT CodingError();

    static CodingError malformed(gint length);

    static CodingError unmappable(gint length);

private:
    CORE_EXPLICIT CodingError(String const &message);
};


#endif //CORE_CODINGERROR_H
