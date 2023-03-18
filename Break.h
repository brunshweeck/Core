//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_BREAK_H
#define CORE_BREAK_H


#include "Error.h"

/**
 * Thrown to indicate end of iteration
 */
class Break final : public Error {
public:
    /**
     * Construct new instance of break
     */
    Break() {}

    /**
     * Return true if specified object is instance of Break Error
     */
    gbool equals(const Object &obj) const override;

    /**
     * Return copy of this instance
     */
    Object &clone() const override;
};


#endif //CORE_BREAK_H
