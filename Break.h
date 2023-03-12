//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_BREAK_H
#define CORE_BREAK_H


#include "Error.h"

/**
 * Thrown to indicate end of iteration
 */
class Break final : Error {
public:
    Break();

    const String &message() const override;

    gbool equals(const Object &obj) const override;


    Object &clone() const override;

    String toString() const override;
};


#endif //CORE_BREAK_H
