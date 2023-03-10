//
// Created by brunshweeck on 08/03/2023.
//

#ifndef CORE_BREAK_H
#define CORE_BREAK_H


#include "Error.h"

/**
 * Thrown to indicate breaking of each action
 */
class Break: public Error {
public:
    CORE_EXPLICIT Break();

    String message() const override;
};


#endif //CORE_BREAK_H
