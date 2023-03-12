//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_IOERROR_H
#define CORE_IOERROR_H


#include "Error.h"

class IOError: public Error {
public:
    IOError();

    explicit IOError(const String &message);

    const String &message() const override;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

    String toString() const override;
};


#endif //CORE_IOERROR_H
