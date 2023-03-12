//
// Created by brunshweeck on 2023/3/12.
//

#ifndef CORE_INDEX_ERROR_H
#define CORE_INDEX_ERROR_H


#include "ValueError.h"

class IndexError : public ValueError {
public:
    IndexError();

    CORE_EXPLICIT IndexError(gint index);

    CORE_EXPLICIT IndexError(glong index);

    CORE_EXPLICIT IndexError(const String &message);

    const String &message() const override;

    gbool equals(const Object &obj) const override;

    Object &clone() const override;

    String toString() const override;
};


#endif //CORE_INDEX_ERROR_H
