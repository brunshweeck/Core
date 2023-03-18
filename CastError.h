//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_CAST_ERROR_H
#define CORE_CAST_ERROR_H


#include "Error.h"

class CastError: public Error {
public:
    /**
     * Construct new instance of Cast error
     */
    CastError() {};

    /**
     * Return copy of this object
     */
    Object &clone() const override;
};


#endif //CORE_CAST_ERROR_H
