//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_CODINGERROR_H
#define CORE_CODINGERROR_H


#include "IOError.h"

class CodingError : public IOError {
public:
    CodingError();

    CORE_EXPLICIT CodingError(const String &message);

    const String &message() const override;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

    String toString() const override;

    static CodingError underflow();

    static CodingError overflow();

    static CodingError malformed(gint length);

    static CodingError unmappable(gint length);
};


#endif //CORE_CODINGERROR_H
