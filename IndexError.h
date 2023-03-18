//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_INDEX_ERROR_H
#define CORE_INDEX_ERROR_H


#include "ValueError.h"

/**
 * Thrown to indicate that index out of bounds
 */
class IndexError : public ValueError {
public:
    /**
     * Construct new instance of Index error
     */
    IndexError() {}

    CORE_EXPLICIT IndexError(gint index);

    CORE_EXPLICIT IndexError(glong index);

    CORE_EXPLICIT IndexError(const String &message);

    Object &clone() const override;
};


#endif //CORE_INDEX_ERROR_H
